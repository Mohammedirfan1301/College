package uml_alerts.uml_alerts;

import android.app.Activity;
import android.content.Intent;
import android.os.Bundle;
import android.support.v4.app.Fragment;
import android.support.v4.app.FragmentManager;
import android.support.v4.widget.DrawerLayout;
import android.support.v7.app.ActionBarActivity;
import android.util.Log;
import android.view.LayoutInflater;
import android.view.MenuItem;
import android.view.View;
import android.view.ViewGroup;
import android.widget.Toast;

import com.google.android.gms.maps.CameraUpdateFactory;
import com.google.android.gms.maps.GoogleMap;
import com.google.android.gms.maps.MapFragment;
import com.google.android.gms.maps.model.LatLng;
import com.google.android.gms.maps.model.MarkerOptions;
import com.opencsv.CSVReader;

import java.io.FileReader;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.HashMap;
import java.util.List;

public class GoogleMaps extends ActionBarActivity
        implements NavigationDrawerFragment.NavigationDrawerCallbacks {


    /**
     *      Top of this file includes member variables and default Android methods
     *
     */

    // Fragment managing the behaviors, interactions and presentation of the navigation drawer.
    private NavigationDrawerFragment mNavigationDrawerFragment;

    // Used to store the last screen title. For use in {@link #restoreActionBar()}.
    private CharSequence mTitle;
    GoogleMap googleMap;

    // App Log Tag.
    private static final String APP_TAG = "UML ALERTS";

    // Fix bug that launches alerts instead of Google Maps.
    private boolean first_boot = true;

    // Previous Alerts filename
    private static final String MAPS_FILE = "maps.csv";

    // Map for the previous alerts
    // Key: date
    // Value: location
    List<HashMap<String, String>> alerts_map;

    // Location Manager.
    GPSTracker gps;


    @Override
    protected void onCreate(Bundle savedInstanceState) {
        Log.v("onCreate()", "Starting onCreate() in GoogleMaps.java");

        super.onCreate(savedInstanceState);
        setContentView(R.layout.google_maps);

        mNavigationDrawerFragment = (NavigationDrawerFragment) getSupportFragmentManager().findFragmentById(R.id.navigation_drawer);
        mTitle = getTitle();

        // Set up the drawer.
        mNavigationDrawerFragment.setUp(R.id.navigation_drawer, (DrawerLayout) findViewById(R.id.drawer_layout));

        // I made this method public and preset the selected item to the Google Maps view.
        // This way, we don't load the first item which defaults to the Alerts view, causing the
        // user to have to hit the back button in order to get to the Google Maps view!
        // We should also be doing this in any function that changes the layout of the app.
        mNavigationDrawerFragment.selectItem(3);

        // Setup the alerts_map list.
        alerts_map = new ArrayList<>();

        // Try and open / read from the CSV file.
        // This will be done in the background to speed up the loading of the Google Maps View.
        openCSV();

        // Setup the location stuff.
        gps = new GPSTracker(this);
        if(gps.canGetLocation()) {
            double latitude = gps.getLatitude();
            double longitude = gps.getLongitude();

            // Show location to logcat.
            Log.v("onCreate()", "Your Location is - \nLat: " + latitude + "\nLong: " + longitude);

        }else{
            // Can't get location
            // GPS or Network is not enabled
            // Ask user to enable GPS/network in settings
            gps.showSettingsAlert();
        }

        // Doing a quick test for efficiency
//        createMapView();
//        addMarker();

        // Get which view we should load - could be Alerts, Contacts or Previous Alerts
//        Bundle b = getIntent().getExtras();
//        int value;
//
//        try {
//            value = b.getInt("key");
//        }
//        catch(Exception e) {
//            Log.v("onCreate()", "Failed to get Int from Bundle. (IN GOOGLEMAPS.JAVA)");
//            value = 3;      // Set default value.
//        }
//
//        // Pick which view should be set.
//        switch(value) {
//            // Loads the Alerts screen
//            case 0:
//                mNavigationDrawerFragment.selectItem(0);
//                break;
//
//            // Loads the Contacts screen
//            case 1:
//                mNavigationDrawerFragment.selectItem(1);
//                break;
//
//            // Loads the Previous Alerts screen.
//            case 2:
//                mNavigationDrawerFragment.selectItem(2);
//                break;
//
//            // on default, load Alerts view. Ex: User first opens app.
//            default:
//                // Loads the ListView up with alerts.
//                mNavigationDrawerFragment.selectItem(3);
//                createMapView();
//                addMarker();
//                break;
//        }
    }


    @Override
    protected void onResume() {
        super.onResume();

        Log.v("onResume()", "Starting onResume() in GoogleMaps.java");

        try {
            // Try and open / read from the CSV file.
            openCSV();
        } catch (Exception e) {
            // Do stuff with the exception.
            Log.v(APP_TAG, "Couldn't open CSV file!", e);
        }

        createMapView();
        addMarker();
    }


    @Override
    public void onPause() {
        super.onPause();  // Always call the superclass method first

        Log.v(APP_TAG, "Starting onPause()... in GoogleMaps.java");

        // Stop listening to the location.
        gps.stopUsingGPS();
    }


    @Override
    public void onNavigationDrawerItemSelected(int position) {
        // update the main content by replacing fragments
        FragmentManager fragmentManager = getSupportFragmentManager();
        fragmentManager.beginTransaction()
                .replace(R.id.container, PlaceholderFragment.newInstance(position + 1))
                .commit();
    }


    /**
     *      Below this line is code for the map of alerts.
     *
     */


    /**
     * Initialises the mapview
     */
    private void createMapView(){
        /**
         * Catch the null pointer exception that
         * may be thrown when initialising the map
         */
        try {
            if(null == googleMap){
                googleMap = ((MapFragment) getFragmentManager().findFragmentById(R.id.mapView)).getMap();

                // Zoom the Google Maps to the user's current location.
                double latitude = gps.getLatitude();
                double longitude = gps.getLongitude();

                googleMap.moveCamera( CameraUpdateFactory.newLatLngZoom(new LatLng(latitude, longitude), 10.0f) );

                /**
                 * If the map is still null after attempted initialisation,
                 * show an error to the user
                 */
                if(null == googleMap) {
                    Toast.makeText(getApplicationContext(),
                            "Error creating map", Toast.LENGTH_SHORT).show();
                }
            }
        } catch (NullPointerException exception){
            Log.e("mapApp", exception.toString());
        }
    }

    /**
     * Adds a marker to the map
     */
    private void addMarker(){

        /** Make sure that the map has been initialised **/
        if(null != googleMap) {
            String date, location;

            /** Add markers for all of the previous alerts. **/
            for (int a = 0; a < alerts_map.size(); a++) {
                HashMap<String, String> tmpData = alerts_map.get(a);

                date = tmpData.get("date");
                location = tmpData.get("location");

                // This was for debugging.
                //String next = date + "," + location;
                //Log.v("Testing current pair: ", next);

                // Need to split the location for providing it as a Google Maps marker.
                String[] parts = location.split("_");
                String Latitude = parts[0];
                String Longitude = parts[1];

                // Convert the lat / long to doubles
                Double Lat = Double.parseDouble(Latitude);
                Double Long = Double.parseDouble(Longitude);

                googleMap.addMarker(new MarkerOptions()
                                .position(new LatLng(Lat, Long))
                                .title("Alert Time: " + date)
                                .draggable(false)
                );
            }
        }
    }


    // Pulls data from the user's contacts book into the contacts map.
    public void openCSV() {
        // Opening CSV file log.
        Log.v(APP_TAG, "Starting OpenCSV()...In GoogleMaps.java");

        try {
            openCSVInBackGround();
        }
        catch(Exception e) {
            // Do stuff with the exception.
            Log.v(APP_TAG, "Couldn't openCSV file! (In GoogleMaps.java)", e);
        }
    }


    // Open data from a CSV file, save to the map.
    public void openCSVInBackGround() throws Exception {
        // This part opens the map data from a CSV file called "maps.csv"
        // Get path for storing / accessing the CSV file.
        String csv_path = android.os.Environment.getExternalStorageDirectory().getAbsolutePath() + "/" + MAPS_FILE;

        // Open data from the CSV file
        String lines[];

        // Build an instance of the CSVReader class. Give it the CSV file's name.
        CSVReader reader = new CSVReader(new FileReader(csv_path));

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
    }



    /**
     *      Below this line is misc. stuff, mostly related to the sidebar.
     */

    // This is for the sidebar drawer
    // NOTE - IT DEFAULTS TO 0 + 1, OR TO POSITION 1!
    // That is what caused issues with loading the Google Maps view!
    public void onSectionAttached(int number) {
        switch (number) {
            case 1:
                // This sets up the alerts view.
                if(first_boot) {
                    first_boot = false;
                }
                else {
                    mTitle = getString(R.string.title_section1);
                    mNavigationDrawerFragment.changeTitle(mTitle);
                    launchAlerts();
                }
                break;
            case 2:
                // This sets up the contacts view.
                mTitle = getString(R.string.title_section2);
                mNavigationDrawerFragment.changeTitle(mTitle);
                launchContacts();
                break;
            case 3:
                // This sets up the previous alerts view
                mTitle = getString(R.string.title_section3);
                mNavigationDrawerFragment.changeTitle(mTitle);
                launchPreviousAlerts();
                break;
            case 4:
                // This sets up the google maps view.
                mTitle = getString(R.string.title_section4);
                mNavigationDrawerFragment.changeTitle(mTitle);
                break;
            case 5:
                // This loads the about page.
                mTitle = getString(R.string.title_section5);
                mNavigationDrawerFragment.changeTitle(mTitle);
                viewAbout();
                break;
        }
    }


    // Launches alerts / contacts activity
    public void launchAlerts() {
        Log.v(APP_TAG, "Starting launchAlerts(). In GoogleMaps.java");

        Intent myIntent = new Intent(GoogleMaps.this, MainActivity.class);
        Bundle b = new Bundle();
        b.putInt("key", 0);         // ID of the page to be loaded.
        myIntent.putExtras(b);      // Put the ID in the intent.
        startActivity(myIntent);
    }


    // Launches alerts / contacts activity
    public void launchContacts() {
        Log.v(APP_TAG, "Starting launchAlerts(). In GoogleMaps.java");

        Intent myIntent = new Intent(GoogleMaps.this, MainActivity.class);
        Bundle b = new Bundle();
        b.putInt("key", 1);         // ID of the page to be loaded.
        myIntent.putExtras(b);      // Put the ID in the intent.
        startActivity(myIntent);
    }


    // Launches alerts / contacts activity
    public void launchPreviousAlerts() {
        Log.v(APP_TAG, "Starting launchAlerts(). In GoogleMaps.java");

        Intent myIntent = new Intent(GoogleMaps.this, MainActivity.class);
        Bundle b = new Bundle();
        b.putInt("key", 2);         // ID of the page to be loaded.
        myIntent.putExtras(b);      // Put the ID in the intent.
        startActivity(myIntent);
    }


    // Launches the About activity
    public void viewAbout() {
        Log.v(APP_TAG, "Starting viewAbout()...In GoogleMaps.java");

        // Launches a new activity.
        Intent myIntent = new Intent(GoogleMaps.this, About.class);
        startActivity(myIntent);

        // After we get back here from the user hitting the back button,
        // reset the title to the Google Maps title.
        mTitle = getString(R.string.title_section4);
        mNavigationDrawerFragment.selectItem(3);
    }


    /**
     * Sets up the menu bar items.
     * Adds:
     * 1) Alerts link
     * 2) Contacts link
     * 3) Google Maps link
     * 4) About link
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
            ((GoogleMaps) activity).onSectionAttached(getArguments().getInt(ARG_SECTION_NUMBER));
        }
    }

    /** Adds options to the menu at the top of the app.
     * This currently isn't used, so it is commented out for now.
     */
//    @Override
//    public boolean onCreateOptionsMenu(Menu menu) {
//        if (!mNavigationDrawerFragment.isDrawerOpen()) {
//            // Only show items in the action bar relevant to this screen
//            // if the drawer is not showing. Otherwise, let the drawer
//            // decide what to show in the action bar.
//            getMenuInflater().inflate(R.menu.main, menu);
//            restoreActionBar();
//            return true;
//        }
//        return super.onCreateOptionsMenu(menu);
//    }

}
