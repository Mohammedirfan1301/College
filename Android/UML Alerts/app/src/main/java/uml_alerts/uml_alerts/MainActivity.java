package uml_alerts.uml_alerts;

import android.app.Activity;
import android.app.AlertDialog;
import android.content.DialogInterface;
import android.content.Intent;
import android.database.Cursor;
import android.os.Bundle;
import android.provider.ContactsContract;
import android.support.v4.app.Fragment;
import android.support.v4.app.FragmentManager;
import android.support.v4.widget.DrawerLayout;
import android.support.v7.app.ActionBarActivity;
import android.telephony.SmsManager;
import android.util.Log;
import android.util.SparseBooleanArray;
import android.view.Gravity;
import android.view.LayoutInflater;
import android.view.MenuItem;
import android.view.View;
import android.view.ViewGroup;
import android.widget.AdapterView;
import android.widget.Button;
import android.widget.EditText;
import android.widget.LinearLayout;
import android.widget.ListView;
import android.widget.SimpleAdapter;
import android.widget.TextView;
import android.widget.Toast;

import com.opencsv.CSVReader;
import com.opencsv.CSVWriter;

import java.io.FileReader;
import java.io.FileWriter;
import java.text.DateFormat;
import java.text.SimpleDateFormat;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.Calendar;
import java.util.Collections;
import java.util.Comparator;
import java.util.Date;
import java.util.HashMap;
import java.util.HashSet;
import java.util.Iterator;
import java.util.LinkedHashMap;
import java.util.LinkedList;
import java.util.List;
import java.util.Map;
import java.util.Set;


/**
 *     ====================
 *     Long Term To Do List
 *     ====================
 *
 *  1. Save the CSV files in a folder - not directly on the SD CARD.
 *     - This should be a simple fix, call mkdir() or something.
 *     See: https://stackoverflow.com/questions/15138695/how-to-make-folder-in-sdcard-in-android
 *
 *  2. Fix loading Contacts / Previous alerts in the Google Maps activity - currently defaults
 *     to Alerts, rather than Contacts / Previous Alerts
 *
 *  3. Consider supporting MMS messaging, to avoid the 160 character limit.
 *     OR: show character count remaining in the alert
 *     OR: allow email alerts
 *     OR: support IM alerts via Google Hangouts / Facebook Messenger
 *
 *
 */


public class MainActivity extends ActionBarActivity
        implements NavigationDrawerFragment.NavigationDrawerCallbacks {

    // Used to store the last screen title. For use in {@link #restoreActionBar()}.
    private CharSequence mTitle;

    // Navigation bar variable stored here.
    NavigationDrawerFragment mNavigationDrawerFragment;

    // Google Maps base URL
    private static final String maps_URL = "http://maps.google.com/maps?z=1&h=m&q=loc:";

    // Const file name for the CSV file.
    private static final String CSV_FILE = "alerts.csv";
    private static final String MAPS_FILE = "maps.csv";

    // App Log Tag.
    private static final String APP_TAG = "UML ALERTS";

    // Map for the Alerts.
    // Key: Phone Number (in String form) - separated by newlines for multiple numbers.
    // Value: Message
    Map<String, String> alerts_list = new HashMap<>();

    // Map for the contacts
    // Key: Name
    // Value: Phone Number
    ArrayList<HashMap<String, String>> contactData;

    // Map for the previous alerts
    // Key: date
    // Value: location
    ArrayList<HashMap<String, String>> alerts_map;

    // ListView to display the alerts.
    ListView alert_list;

    // ListView to display the contacts
    ListView contacts_list;

    // ListView to display the previous alerts.
    ListView previous_list;

    // Adapter for the ListView.
    SimpleAdapter list_adapter;

    // ArrayList for the ListView
    List<Map<String, String>> list;

    // Add Alert button
    Button addAlertButton;

    // User input variables from the dialog for entering a phone number / message
    String mMessage = "";
    String mPhone = "";

    // Location Manager.
    GPSTracker gps;


    /**
     *      Android related methods are at the top.
     *      Other app related methods are below the Android stuff.
     */
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        // Logcat, one for every function / method.
        Log.v(APP_TAG, "Starting onCreate() in MainActivity.java");

        /**
         *      Setup the location stuff.
         *      Doing this first to grab the location as fast as possible.
         */
        gps = new GPSTracker(this);
        if(gps.canGetLocation()) {
            double latitude = gps.getLatitude();
            double longitude = gps.getLongitude();

            // Show location to logcat.
            Log.v("onCreate()", "Your Location is - \nLat: " + latitude + "\nLong: " + longitude);

        }else{
            // Can't get location, as GPS or Network is not enabled
            // Ask user to enable GPS/Network in settings
            gps.showSettingsAlert();
        }

        // Setup the alerts_map list.
        alerts_map = new ArrayList<>();

        /**    Opens the CSV files - alerts / previous alerts maps data.    **/
        try {
            // Try and open / read from the CSV file.
            OpenCSV();
        } catch (Exception e) {
            // Do stuff with the exception.
            Log.v(APP_TAG, "Couldn't open CSV file! In MainActivity.java", e);
        }

        // Get the contact data into the ArrayList.
        getContacts();

        /** This part sets up the Navigation Drawer.  **/
        // Fragment managing the behaviors, interactions and presentation of the navigation drawer.
        mNavigationDrawerFragment = (NavigationDrawerFragment)
                getSupportFragmentManager().findFragmentById(R.id.navigation_drawer);
        mTitle = getTitle();

        // Set up the drawer.
        mNavigationDrawerFragment.setUp(
                R.id.navigation_drawer,
                (DrawerLayout) findViewById(R.id.drawer_layout));

        // Get which view we should load - could be Alerts, Contacts or Previous Alerts
        Bundle b = getIntent().getExtras();
        int value;

        try {
            value = b.getInt("key");
        }
        catch(Exception e) {
            Log.v("onCreate()", "Failed to get Int from Bundle. In MainActivity.java");
            value = 0;      // Set default value.
        }

        // Pick which view should be set.
        switch(value) {
            // Loads the Alerts screen
            case 0:
                mNavigationDrawerFragment.selectItem(0);
                mTitle = getString(R.string.title_section1);
                mNavigationDrawerFragment.changeTitle(mTitle);
                break;

            // Loads the Contacts screen
            case 1:
                mNavigationDrawerFragment.selectItem(1);
                mTitle = getString(R.string.title_section2);
                mNavigationDrawerFragment.changeTitle(mTitle);
                break;

            // Loads the Previous Alerts screen.
            case 2:
                mNavigationDrawerFragment.selectItem(2);
                mTitle = getString(R.string.title_section3);
                mNavigationDrawerFragment.changeTitle(mTitle);
                break;

                // on default, load Alerts view. Ex: User first opens app.
            default:
                // Loads the ListView up with alerts.
                mNavigationDrawerFragment.selectItem(0);
                mTitle = getString(R.string.title_section1);
                mNavigationDrawerFragment.changeTitle(mTitle);
                createAlerts();

                addAlertButton = (Button) findViewById(R.id.AddAlertButton);
                addAlertButton.setOnClickListener(new View.OnClickListener() {
                    public void onClick(View view) {
                        AddAlert();
                    }
                });
                break;
        }
    }


    @Override
    public void onPause() {
        super.onPause();  // Always call the superclass method first

        Log.v(APP_TAG, "Starting onPause()...In MainActivity.java");

        // Stop listening to the location.
        gps.stopUsingGPS();

        // Call the SaveCSV function to save the map data to a CSV file.
        try {
            SaveCSV();
        } catch (Exception e) {
            // Write exception to logcat.
            Log.v(APP_TAG, "Error! Couldn't save file to CSV! In MainActivity.java", e);
        }
    }


    @Override
    public void onResume() {
        super.onResume();  // Always call the superclass method first
        Log.v(APP_TAG, "Starting onResume()...In MainActivity.java");

        // Update the location.
        if(gps.canGetLocation()) {
            double latitude = gps.getLatitude();
            double longitude = gps.getLongitude();

            // Show location to logcat.
            Log.v("onCreate()", "Your Location is - \nLat: " + latitude + "\nLong: " + longitude);

        }else{
            // can't get location
            // GPS or Network is not enabled
            // Ask user to enable GPS/network in settings
            gps.showSettingsAlert();
        }

        /**    Opens the CSV files - alerts / previous alerts maps data.    **/
        try {
            // Try and open / read from the CSV file.
            OpenCSV();
        } catch (Exception e) {
            // Do stuff with the exception.
            Log.v(APP_TAG, "Couldn't open CSV file! In MainActivity.java", e);
        }

        // Get the contact data into the ArrayList.
        getContacts();
    }


    // This is for the sidebar drawer
    @Override
    public void onNavigationDrawerItemSelected(int position) {
        // update the main content by replacing fragments
        FragmentManager fragmentManager = getSupportFragmentManager();
        fragmentManager.beginTransaction()
                .replace(R.id.container, PlaceholderFragment.newInstance(position + 1))
                .commit();
    }


    // This is for the sidebar drawer
    public void onSectionAttached(int number) {
        switch (number) {
            case 1:
                // This sets up the alerts view.
                mTitle = getString(R.string.title_section1);
                mNavigationDrawerFragment.changeTitle(mTitle);
                createAlerts();
                break;
            case 2:
                // This sets up the contacts view.
                mTitle = getString(R.string.title_section2);
                mNavigationDrawerFragment.changeTitle(mTitle);
                // Get the contact data into the ArrayList.
                getContacts();
                createContacts();
                break;
            case 3:
                // This sets up the previous alerts view
                mTitle = getString(R.string.title_section3);
                mNavigationDrawerFragment.changeTitle(mTitle);
                createPreviousAlerts();
                break;
            case 4:
                // This sets up the google maps view.
                mTitle = getString(R.string.title_section4);
                mNavigationDrawerFragment.changeTitle(mTitle);
                launchMaps();
                break;
            case 5:
                // This loads the about page.
                mTitle = getString(R.string.title_section5);
                mNavigationDrawerFragment.changeTitle(mTitle);
                viewAbout();
                break;
        }
    }


    public void launchMaps() {
        Log.v(APP_TAG, "Starting Google Maps View...In MainActivity.java");

        // Launches a new activity.
        Intent myIntent = new Intent(MainActivity.this, GoogleMaps.class);
        Bundle b = new Bundle();
        b.putInt("key", 3);         // ID of the page to be loaded.
        myIntent.putExtras(b);      // Put the ID in the intent.
        startActivity(myIntent);

        // After the Google Maps page launches, the view resets to the Alert's page,
        // so we should reset the title in the Sidebar as well!
        mTitle = getString(R.string.title_section1);
        mNavigationDrawerFragment.selectItem(0);
    }


    // Launches the About activity
    public void viewAbout() {
        Log.v(APP_TAG, "Starting viewAbout()...In MainActivity.java");

        // Launches a new activity.
        Intent myIntent = new Intent(MainActivity.this, About.class);
        MainActivity.this.startActivity(myIntent);

        // After the About page loads and the user returns by hitting the back button, we should
        // reset the view to the alerts page and make the title the Alerts title.
        mTitle = getString(R.string.title_section1);
        mNavigationDrawerFragment.selectItem(0);
    }


    // Open data from a CSV file, save to the map.
    public void OpenCSV() throws Exception {
        // Opening CSV file log.
        Log.v(APP_TAG, "Starting OpenCSV()...In MainActivity.java");

        // The first part opens the alerts data from a CSV file called "alerts.csv"
        // Get path for storing / accessing the CSV file.
        String csv_path = android.os.Environment.getExternalStorageDirectory().getAbsolutePath() + "/" + CSV_FILE;

        // Open data from the CSV file
        String line[];

        // Build an instance of the CSVReader class. Give it the CSV file's name.
        CSVReader reader = new CSVReader(new FileReader(csv_path));

        // Read all the data off the CSV file.
        line = reader.readNext();

        while (line != null) {
            // This gets the line and splits it based on the comma.
            List<String> container = Arrays.asList(line);

            // This gets the key / value from the List container.
            String key = container.get(0);
            String value = container.get(1);

            // Add to the map.
            alerts_list.put(key, value);

            // Get the next line.
            line = reader.readNext();
        }

        // This second part opens the map data from a CSV file called "maps.csv"
        // Get path for storing / accessing the CSV file.
        csv_path = android.os.Environment.getExternalStorageDirectory().getAbsolutePath() + "/" + MAPS_FILE;

        // Open data from the CSV file
        String lines[];

        // Build an instance of the CSVReader class. Give it the CSV file's name.
        reader = new CSVReader(new FileReader(csv_path));

        // Read all the data off the CSV file.
        lines = reader.readNext();

        while (lines != null) {
            // This gets the line and splits it based on the comma.
            List<String> container = Arrays.asList(lines);

            // This gets the key / value from the List container.
            String key = container.get(0);
            String value = container.get(1);

            // Debugging
//            Log.v("Key is: ", key);
//            Log.v("Value is: ", value);

            HashMap<String, String> map = new HashMap<>();
            map.put("date", key);
            map.put("location", value);
            alerts_map.add(map);

            // Get the next line.
            lines = reader.readNext();
        }

        // Remove duplicates from the ArrayList by adding it to a Set.
        Set<HashMap<String, String>> tmp = new HashSet<>();

        // THIS WILL REMOVE ALL DUPLICATES FROM THE ARRAY LIST.
        tmp.addAll(alerts_map);
        alerts_map.clear();
        alerts_map.addAll(tmp);

        // Now update the alerts view.
        updateListView();
    }


    // Read from CSV file into local map variable.
    public void SaveCSV() throws Exception {
        // Opening CSV file log.
        Log.v(APP_TAG, "Starting SaveCSV()...In MainActivity.java");

        // The first part saves the alerts data to a CSV file called "alerts.csv"
        // Get path for storing / accessing the CSV file.
        String csv_path = android.os.Environment.getExternalStorageDirectory().getAbsolutePath() + "/" + CSV_FILE;

        // Create an instance of the CSVWriter class. Give it the CSV file's name.
        CSVWriter writer = new CSVWriter(new FileWriter(csv_path));

        // While we've got a valid thing in the map.
        for (Map.Entry<String, String> entry : alerts_list.entrySet()) {
            // Now pair will have a key / value that we can save.
            String key = entry.getKey();
            String value = entry.getValue();
            String next = key + "," + value;

            String[] cur_alert = next.split(",");
            writer.writeNext(cur_alert);
        }

        // Close the writer.
        writer.close();

        // This second part saves the map data to a CSV file called "maps.csv"
        // Get path for storing / accessing the CSV file.
        csv_path = android.os.Environment.getExternalStorageDirectory().getAbsolutePath() + "/" + MAPS_FILE;

        // Create an instance of the CSVWriter class. Give it the CSV file's name.
        writer = new CSVWriter(new FileWriter(csv_path));

        String date, location;

        for (int a = 0; a < alerts_map.size(); a++) {
            HashMap<String, String> tmpData = alerts_map.get(a);

            date = tmpData.get("date");
            location = tmpData.get("location");
            String next = date + "," + location;

            // Old Debugging Log.
            //Log.v("Testing current pair: ", next);

            String[] cur_alert = next.split(",");
            writer.writeNext(cur_alert);
        }

        // Close the writer.
        writer.close();
    }


    // This builds up the alerts ArrayList
    private ArrayList<Map<String, String>> buildData() {
        // This will at some point pull from the alerts_list map!
        // For now it is hard coded for testing purposes.
        Log.v(APP_TAG, "Starting buildData()...In MainActivity.java");

        ArrayList<Map<String, String>> tmp_list = new ArrayList<>();

        for (Map.Entry<String, String> entry : alerts_list.entrySet()) {
            tmp_list.add(putData(entry.getKey(), entry.getValue()));
        }

        return tmp_list;
    }


    // This is used by the above buildData as a helper method to generate the ArrayList
    // from the alerts map.
    private HashMap<String, String> putData(String phone_number, String alert) {
        //Log.v(APP_TAG, "Starting putData()...In MainActivity.java");

        HashMap<String, String> item = new HashMap<>();
        item.put("phone_number", phone_number);
        item.put("alert", alert);
        return item;
    }


    // Technically this just redoes the list view stuff.
    // Don't really need this method if we're going to do it the lazy way.
    public void updateListView() {
        Log.v(APP_TAG, "Starting updateListView()...In MainActivity.java");
        createAlerts();
    }


    // Adds all the alerts to the list view.
    private void createAlerts() {
        Log.v("createListView", "Starting createListView()...In MainActivity.java");

        // Get the list view from the XML file.
        alert_list = (ListView) findViewById(R.id.listView);

        // Onclick listener for the alerts.
        alert_list.setOnItemClickListener(new AdapterView.OnItemClickListener() {
            public void onItemClick(AdapterView<?> parent, View view, int position, long id) {

                // Get the phone number(s) and the alert from the ListView
                Object obj = (alert_list.getItemAtPosition(position));
                HashMap<String, String> item = (HashMap<String, String>) obj;
                String phoneNumber = item.get("phone_number");
                String alert = item.get("alert");

                sendSMSMessage(phoneNumber, alert);
            }
        });

        // Long click listener for deleting alerts
        alert_list.setOnItemLongClickListener(new AdapterView.OnItemLongClickListener() {
            public boolean onItemLongClick(AdapterView<?> parent, View view, final int position, long id) {

                // Make a popup to confirm if the user actually wants to delete this alert.
                AlertDialog.Builder deleteAlert = new AlertDialog.Builder(MainActivity.this);

                deleteAlert.setMessage("Remove this alert?");
                deleteAlert.setPositiveButton("DELETE", new AlertDialog.OnClickListener() {
                    public void onClick(DialogInterface dialog, int which) {
                        // Get the phone number(s) from the ListView
                        Object obj = (alert_list.getItemAtPosition(position));
                        HashMap<String, String> item = (HashMap<String, String>) obj;
                        String phoneNumber = item.get("phone_number");

                        Log.v("Deleting phone number: ", phoneNumber);

                        // Delete the alert from the map.
                        for(Iterator<Map.Entry<String, String>> it = alerts_list.entrySet().iterator(); it.hasNext(); ) {
                            Map.Entry<String, String> entry = it.next();

                            // Only remove the alert with the matching phone number!
                            if (entry.getValue().equals(phoneNumber)) {
                                it.remove();
                            }
                        }

                        // Now refresh the ListView's adapter.
                        alerts_list.remove(phoneNumber);
                        list_adapter.notifyDataSetChanged();
                        createAlerts();
                    }

                }).setNegativeButton("CANCEL", new AlertDialog.OnClickListener() {
                    public void onClick(DialogInterface dialog, int which) {
                        // Does nothing but cancel the delete alert.
                    }
                });

                // Display the dialog.
                deleteAlert.show();

                return false;
            }
        });

        // Setup the Add alerts button.
        addAlertButton = (Button) findViewById(R.id.AddAlertButton);
        addAlertButton.setOnClickListener(new View.OnClickListener() {
            public void onClick(View view) {
                AddAlert();
            }
        });

        // Sort the alerts.
        alerts_list = sortByKeys(alerts_list);

        // Create a list of two items.
        // One is the user's phone number.
        // The other is the alert message.
        list = buildData();

        // From is a list of Key's.
        // to is an array of IDs for the strings.
        String[] from = {"phone_number", "alert"};
        int[] to = {android.R.id.text1, android.R.id.text2};

        // Simple adapter is all we need for this.
        list_adapter = new SimpleAdapter(this, list, android.R.layout.simple_list_item_2, from, to);
        alert_list.setAdapter(list_adapter);
    }


    // This alerts an alert to the map, and onPause saves the map data to a csv file.
    // Makes a simple alert dialog with its own view stuff.
    public void AddAlert() {
        Log.i(APP_TAG, "Starting AddAlert()...");

        // Remove duplicates from the contactsData ArrayList by adding it to a Set.
        Set<HashMap<String, String>> tmp = new HashSet<>();

        // THIS WILL REMOVE ALL DUPLICATES FROM THE ARRAY LIST.
        tmp.addAll(contactData);
        contactData.clear();
        contactData.addAll(tmp);

        // Text entry dialog.
        AlertDialog.Builder text_entry = new AlertDialog.Builder(this);

        TextView Title = new TextView(this);
        Title.setText("Add New Alert");
        Title.setTextAppearance(this, android.R.style.TextAppearance_Large);
        Title.setGravity(Gravity.CENTER_HORIZONTAL);

        TextView Msg = new TextView(this);
        Msg.setText("Please add a contact(s) and a message for this alert.");
        Msg.setGravity(Gravity.CENTER_HORIZONTAL);

        // ** Display a list of contacts that we want to select from. **
        // Get the list view from the XML file.
        final ListView contact_list = new ListView(this);

        // From is a list of Key's.
        // to is an array of IDs for the strings.
        String[] from = {"name", "number"};
        int[] to = {android.R.id.text1, android.R.id.text2};

        // Sort the contacts in order.
        Collections.sort(contactData, new MapComparator("name"));

        // Simple adapter is all we need for this.
        list_adapter = new SimpleAdapter(this, contactData, android.R.layout.simple_list_item_multiple_choice, from, to);

        // Allow multiple choices for the list view.
        // See the following site for help:
        // http://theopentutorials.com/tutorials/android/listview/android-multiple-selection-listview/
        contact_list.setChoiceMode(ListView.CHOICE_MODE_MULTIPLE);
        contact_list.setAdapter(list_adapter);

        // Get the message
        final EditText msg_input = new EditText(this);
        msg_input.setHint("Enter your message here.");
        msg_input.setGravity(Gravity.START);

        // Create a layout for the title, about and two input strings.
        LinearLayout lay = new LinearLayout(this);
        lay.setOrientation(LinearLayout.VERTICAL);
        lay.addView(Title);
        lay.addView(Msg);
        lay.addView(msg_input);
        lay.addView(contact_list);
        text_entry.setView(lay);

        // Set the title / message / positive & negative buttons.
        text_entry.setPositiveButton("Done.", new DialogInterface.OnClickListener() {
            public void onClick(DialogInterface dialog, int whichButton) {

                // We need to get a list of the people we selected above.
                SparseBooleanArray checked = contact_list.getCheckedItemPositions();
                ArrayList<String> selectedItems = new ArrayList<>();

                for (int i = 0; i < checked.size(); i++) {

                    // Item position in adapter
                    int position = checked.keyAt(i);

                    // Add the contact
                    if (checked.valueAt(i)) {

                        // Get the values from the list.
                        Object obj = (contact_list.getItemAtPosition(position));
                        HashMap<String, String> item = (HashMap<String, String>) obj;

                        // Get just the phone number / contact name.
                        String phoneNumber = item.get("number");
                        String contactName = item.get("name");
                        String alert = contactName + "  " + phoneNumber;

                        // Test log.
                        Log.v("Adding new alert: ", alert);

                        // Add the current number to the ArrayList.
                        selectedItems.add(alert);
                    }
                }

                // Now that we have an array list of strings, we can create the
                // one string that will save all the phone numbers separated by new lines (\n)
                StringBuilder builder = new StringBuilder((""));
                for(String val : selectedItems) {
                    builder.append(val).append("\n");       // Append a newline.
                }
                // Setup phone number / message
                mPhone = builder.toString();
                mMessage = msg_input.getText().toString();

                // Add the phone number / message to the map of alerts.
                alerts_list.put(mPhone, mMessage);

                // Update the ListView.
                updateListView();
            }
        }).setNegativeButton("Cancel", new DialogInterface.OnClickListener() {
            public void onClick(DialogInterface dialog, int whichButton) {
                dialog.cancel();
            }
        });

        // Display the dialog
        text_entry.show();

        // Get a location update whenever alerts are added or sent.
        gps.getLocation();
    }



    // Adds all the user's contacts to the list view.
    private void createContacts() {
        Log.v("createContacts", "Starting createContacts()...In MainActivity.java");

        // Get the list view from the XML file.
        contacts_list = (ListView) findViewById(R.id.listView);

        // Onclick listener for the contacts
        contacts_list.setOnItemClickListener(new AdapterView.OnItemClickListener() {
            public void onItemClick(AdapterView<?> parent, View view, int position, long id) {
                // This does nothing because it shouldn't do anything at all.
            }
        });

        // Make the "add new alert button" actually just pop up the add new contact page.
        // Setup the Add alerts button.
        addAlertButton = (Button) findViewById(R.id.AddAlertButton);
        addAlertButton.setOnClickListener(new View.OnClickListener() {
            public void onClick(View view) {
                AddContact();
            }
        });

        // From is a list of Key's.
        // to is an array of IDs for the strings.
        String[] from = {"name", "number"};
        int[] to = {android.R.id.text1, android.R.id.text2};

        // Sort the contacts in order.
        Collections.sort(contactData, new MapComparator("name"));

        // Simple adapter is all we need for this.
        list_adapter = new SimpleAdapter(this, contactData, android.R.layout.simple_list_item_2, from, to);
        contacts_list.setAdapter(list_adapter);
    }


    public void createPreviousAlerts() {
        Log.v("createPreviousAlerts", "Starting createPreviousAlerts()...In MainActivity.java");

        // Get the list view from the XML file.
        previous_list = (ListView) findViewById(R.id.listView);

        // Onclick listener for the contacts
        previous_list.setOnItemClickListener(new AdapterView.OnItemClickListener() {
            public void onItemClick(AdapterView<?> parent, View view, int position, long id) {
                // This does nothing because it shouldn't do anything at all.
            }
        });

        // Make the "add new alert button" actually just pop up the add new contact page.
        // Setup the Add alerts button.
        addAlertButton = (Button) findViewById(R.id.AddAlertButton);
        addAlertButton.setOnClickListener(new View.OnClickListener() {
            public void onClick(View view) {
                // This does nothing because it shouldn't do anything at all.
            }
        });

        // From is a list of Key's.
        // to is an array of IDs for the strings.
        String[] from = {"date", "location"};
        int[] to = {android.R.id.text1, android.R.id.text2};

        // Try and see if we can get any previous alerts.
        try {
            // Simple adapter is all we need for this.
            list_adapter = new SimpleAdapter(this, alerts_map, android.R.layout.simple_list_item_2, from, to);
            previous_list.setAdapter(list_adapter);
        }
        catch(Exception e) {
            // Do stuff with the exception.
            Log.v(APP_TAG, "Couldn't view previous alerts! In MainActivity.java", e);

            new AlertDialog.Builder(MainActivity.this)
                    .setTitle("No Previous Alerts")
                    .setMessage("You don't have any previous alerts yet! Try sending some! :-D")
                    .setCancelable(false)
                    .setPositiveButton("OK - Got it.", new AlertDialog.OnClickListener() {
                        public void onClick(DialogInterface dialog, int which) {

                        }
                    }).create().show();
        }
    }


    // Simple function for (+) button.
    public void AddContact() {
        Intent intent = new Intent(Intent.ACTION_INSERT, ContactsContract.Contacts.CONTENT_URI);
        startActivity(intent);
    }


    // Pulls data from the user's contacts book into the contacts map.
    // This runs in a new thread, to avoid slowing down the UI.
    public void getContacts() {
        Log.v("getContacts()", "Starting getContacts()...In MainActivity.java");

        new Thread() {
            @Override
            public void run() {
                getContactsInBackground();
            }
        }.start();
    }

    // This code is for displaying contacts.
    // We should in fact search through contacts and save their number in the map instead.
    // May need to make an array of numbers though if more than one.
    // For now deal with just SMS messages so just one number per alert.
    public void getContactsInBackground() {
        contactData = new ArrayList<>();
        Cursor cursor = getContentResolver().query(ContactsContract.Contacts.CONTENT_URI, null, null, null, null);
        while (cursor.moveToNext()) {
            try {
                String contactId = cursor.getString(cursor.getColumnIndex(ContactsContract.Contacts._ID));
                String name = cursor.getString(cursor.getColumnIndex(ContactsContract.Contacts.DISPLAY_NAME));
                if (Integer.parseInt(cursor.getString(cursor.getColumnIndex(ContactsContract.Contacts.HAS_PHONE_NUMBER))) > 0) {
                    Cursor phones = getContentResolver().query(ContactsContract.CommonDataKinds.Phone.CONTENT_URI, null,
                            ContactsContract.CommonDataKinds.Phone.CONTACT_ID + " = " + contactId, null, null);
                    while (phones.moveToNext()) {
                        String phoneNumber = phones.getString(phones.getColumnIndex(ContactsContract.CommonDataKinds.Phone.NUMBER));
                        HashMap<String, String> map = new HashMap<>();
                        map.put("name", name);
                        map.put("number", phoneNumber);
                        contactData.add(map);
                    }
                    phones.close();
                }
            } catch (Exception e) {
                e.printStackTrace();
            }
        }

        cursor.close();
    }


    /**
     *      Method that sends an SMS message to a given phone number.
     *      Needs to have a phone number & message set to be successful.
     *
     *      _phoneNo string works as following:
     *      CONTACT_NAME     CONTACT_NUMBER\n
     *      **if more than one contact, it would appear here **
     *
     *      Multiple numbers are separated by a "\n" and will send
     *      separate SMS messages to those numbers.
     *
     *      Name / Numbers are separated by five space characters.
     */
    protected void sendSMSMessage(final String _phoneNo, final String _message) {
        Log.i("sendSMSMessage()", "Starting to send the SMS message...");

        // Get a location update whenever alerts are added or sent.
        // In this case it is critical to start grabbing an updated location as soon as the user
        // press on the ListView, as if they click "Yes", they will want an updated location and
        // not an old one!
        if(gps.canGetLocation()) {
            gps.getLocation();
        } else {
            // We can't get a location, as GPS or Network is not enabled
            // Ask user to enable GPS/Network in settings
            gps.showSettingsAlert();
        }

        AlertDialog.Builder sms = new AlertDialog.Builder(this);
        sms.setTitle("Send the message?");
        sms.setMessage("Do you really want to send the SMS?");
        sms.setIcon(android.R.drawable.ic_dialog_alert);
        sms.setPositiveButton(android.R.string.yes, new DialogInterface.OnClickListener() {

            public void onClick(DialogInterface dialog, int whichButton) {
                Toast.makeText(MainActivity.this, "Sending Alert(s)", Toast.LENGTH_SHORT).show();

                // Parse the phone number string for (possibly) multiple phone numbers,
                // separated by newlines ("\n")
                List<String> numbers;
                numbers = Arrays.asList(_phoneNo.split("\n"));

                // Pre-set to Olsen Hall, or 42.654802, -71.326363
                double latitude = 42.654802;
                double longitude = -71.326363;
                String location = Double.toString(latitude) + "," + Double.toString(longitude);

                for(String num : numbers) {
                    //Log.v("Sending SMS Alert to: ", num);

                    // Note - we now need to separate the String "num" as we just want
                    // the contacts number, not there name! These are separated by two spaces ("  ")
                    String[] parts = num.split("  ");

                    String phoneNo = parts[1];
                    String message = _message;

                    //Log.v("Sending SMS Alert to: ", phoneNo);

                    // Get the current location.
                    if(gps.canGetLocation()) {
                        latitude = gps.getLatitude();
                        longitude = gps.getLongitude();
                    } else {
                        // can't get location
                        // GPS or Network is not enabled
                        // Ask user to enable GPS/network in settings
                        gps.showSettingsAlert();
                    }

                    // Message for the user explaining why there's a google maps URL at the bottom.
                    String location_msg = "\nLocation: ";
                    location = Double.toString(latitude) + "," + Double.toString(longitude);

                    // Append a google maps URL to the message
                    String maps = maps_URL + location;
                    message += location_msg + maps;

                    try {
                        SmsManager smsManager = SmsManager.getDefault();
                        smsManager.sendTextMessage(phoneNo, null, message, null, null);
                        Toast.makeText(getApplicationContext(), "SMS sent to: " + phoneNo, Toast.LENGTH_SHORT).show();
                    } catch (Exception e) {
                        Toast.makeText(getApplicationContext(), "SMS failed, please try again.", Toast.LENGTH_SHORT).show();
                        e.printStackTrace();
                    }
                }

                // Update the map with a new alert that's been sent.
                // Doing so here to just add one map location, VS a million if the user sent this alert
                // to say 5 or more people.

                // Add a date / time
                DateFormat dateFormat = new SimpleDateFormat("MM/dd/yyyy-HH:mm:ss");
                Date today = Calendar.getInstance().getTime();
                String date = dateFormat.format(today);

                // Create a location string for saving.
                String loc = latitude + "_" + longitude;

                // Create a location string.
                HashMap<String, String> map = new HashMap<>();
                map.put("date", date);
                map.put("location", loc);
                alerts_map.add(map);
                //alerts_map.put(date, location);
            }
        });
        sms.setNegativeButton(android.R.string.no, null);

        AlertDialog dialog = sms.create();
        dialog.show();
    }

    /** Adds options to the menu at the top of the app.
     * This currently isn't used, so it is commented out for now.
     */
    /*
    @Override
    public boolean onCreateOptionsMenu(Menu menu) {
        if (!mNavigationDrawerFragment.isDrawerOpen()) {
            // Only show items in the action bar relevant to this screen
            // if the drawer is not showing. Otherwise, let the drawer
            // decide what to show in the action bar.
            getMenuInflater().inflate(R.menu.main, menu);
            restoreActionBar();
            return true;
        }
        return super.onCreateOptionsMenu(menu);
    }
    */


    /**
     * Sets up the menu bar items.
     * Adds:
     * 1) Alerts link
     * 2) Contacts link
     * 3) Previous Alerts link
     * 4) Google Maps link
     * 5) About link
     */
    @Override
    public boolean onOptionsItemSelected(MenuItem item) {
        // Handle action bar item clicks here. The action bar will
        // automatically handle clicks on the Home/Up button, so long
        // as you specify a parent activity in AndroidManifest.xml.
        int id = item.getItemId();
        return id == R.id.action_settings || super.onOptionsItemSelected(item);
    }


    /**
     * A placeholder fragment containing a simple view.
     */
    public static class PlaceholderFragment extends Fragment {
        /**
         * The fragment argument representing the section number for this
         * fragment.
         */
        private static final String ARG_SECTION_NUMBER = "section_number";

        /**
         * Returns a new instance of this fragment for the given section
         * number.
         */
        public static PlaceholderFragment newInstance(int sectionNumber) {
            PlaceholderFragment fragment = new PlaceholderFragment();
            Bundle args = new Bundle();
            args.putInt(ARG_SECTION_NUMBER, sectionNumber);
            fragment.setArguments(args);
            return fragment;
        }

        public PlaceholderFragment() {
        }

        @Override
        public View onCreateView(LayoutInflater inflater, ViewGroup container,
                                 Bundle savedInstanceState) {
            View rootView = inflater.inflate(R.layout.fragment_main, container, false);
            return rootView;
        }

        @Override
        public void onAttach(Activity activity) {
            super.onAttach(activity);
            ((MainActivity) activity).onSectionAttached(getArguments().getInt(ARG_SECTION_NUMBER));
        }
    }


    // Sorts a HashMap
    public static <K extends Comparable, V extends Comparable> Map<K, V> sortByKeys(Map<K, V> map) {
        List<K> keys = new LinkedList<>(map.keySet());
        Collections.sort(keys);

        //LinkedHashMap will keep the keys in the order they are inserted
        //which is currently sorted on natural ordering
        Map<K, V> sortedMap = new LinkedHashMap<>();
        for (K key : keys) {
            sortedMap.put(key, map.get(key));
        }

        return sortedMap;
    }
}

// Used by the sort HashMap function above.
class MapComparator implements Comparator<Map<String, String>> {
    private final String key;

    public MapComparator(String key) {
        this.key = key;
    }

    public int compare(Map<String, String> first, Map<String, String> second) {
        String firstValue = first.get(key);
        String secondValue = second.get(key);
        return firstValue.compareTo(secondValue);
    }
}