package course.labs.locationlab;

import android.app.ListActivity;
import android.content.Context;
import android.location.Location;
import android.location.LocationListener;
import android.location.LocationManager;
import android.os.Bundle;
import android.util.Log;
import android.view.LayoutInflater;
import android.view.Menu;
import android.view.MenuInflater;
import android.view.MenuItem;
import android.view.View;
import android.view.View.OnClickListener;
import android.widget.TextView;
import android.widget.Toast;

import java.util.ArrayList;

public class PlaceViewActivity extends ListActivity implements LocationListener {
	private static final long FIVE_MINS = 5 * 60 * 1000;

	private static String TAG = "Lab-Location";

	private Location mLastLocationReading;      // The last valid location reading
	private PlaceViewAdapter mAdapter;          // The ListView's adapter

	// default minimum time between new location readings
	private long mMinTime = 5000;

	// default minimum distance between old and new readings.
	private float mMinDistance = 1000.0f;

	// Reference to the LocationManager
	private LocationManager mLocationManager;

	// A fake location provider used for testing
	private MockLocationProvider mMockLocationProvider;

	@Override
	protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);

        if (null == (mLocationManager = (LocationManager) getSystemService(Context.LOCATION_SERVICE))) {
            finish();
        }

        // DONE - Set up the app's user interface
        // This class is a ListActivity, so it has its own ListView
        // ListView's adapter should be a PlaceViewAdapter
        mAdapter = new PlaceViewAdapter(getApplicationContext());
        getListView().setFooterDividersEnabled(true);

        // DONE - add a footerView to the ListView
        // You can use footer_view.xml to define the footer
        LayoutInflater inflater = (LayoutInflater)this.getSystemService(Context.LAYOUT_INFLATER_SERVICE);
        TextView footerView = (TextView)inflater.inflate(R.layout.footer_view, null);
        getListView().addFooterView(footerView);

        footerView.setOnClickListener(new OnClickListener() {

            @Override public void onClick(View arg0) {

                // When the footerView's onClick() method is called, it must issue the follow log call
                log("Entered footerView.OnClickListener.onClick()");

                // Must handle 3 cases:
                // 1) The current location is new - download new Place Badge.
                // 2) The current location has been seen before - issue Toast message.
                // 3) There is no current location - response is up to you.

                // Case 3
                if (mLastLocationReading == null)
                {
                    log("Location data is unavailable at the moment. Please try again later.");
                    Toast.makeText(getApplicationContext(),
                          "Location data is unavailable.",
                          Toast.LENGTH_SHORT).show();
                }

                // Case 1
                if(!mAdapter.intersects(mLastLocationReading))
                {
                    log("Starting Place Download");

                    Toast.makeText(getApplicationContext(),
                          "Starting Place Download",
                          Toast.LENGTH_SHORT).show();

                    PlaceDownloaderTask PDtask = new PlaceDownloaderTask(PlaceViewActivity.this);
                    PDtask.execute(mLastLocationReading);
                }

                // Case 2
                else {
                    log("You already have this location badge");
                    Toast.makeText(getApplicationContext(),
                          "You already have this location badge!",
                          Toast.LENGTH_SHORT).show();
                }
            }
        });

        // Attach the adapter to this ListActivity's ListView
        getListView().setAdapter(mAdapter);
	}

	@Override
	protected void onResume() {
		super.onResume();

		mMockLocationProvider = new MockLocationProvider(LocationManager.NETWORK_PROVIDER, this);

		// DONE - Check NETWORK_PROVIDER for an existing location reading.
        mLastLocationReading = mLocationManager.getLastKnownLocation(LocationManager.NETWORK_PROVIDER);

        // Only keep the reading if it is less than 5 minutes old.
        if (mLastLocationReading != null) {
            if (age(mLocationManager.getLastKnownLocation(LocationManager.NETWORK_PROVIDER)) > FIVE_MINS) {
                mLastLocationReading = null;
            }
        }

        // DONE - register to receive location updates from NETWORK_PROVIDER
        mLocationManager.requestLocationUpdates(LocationManager.NETWORK_PROVIDER, mMinTime, mMinDistance, this);
	}

	@Override
	protected void onPause() {

		mMockLocationProvider.shutdown();

        // DONE - unregister for location updates
        mLocationManager.removeUpdates(this);

		super.onPause();
	}

	public void addNewPlace(PlaceRecord place) {

		log("Entered addNewPlace()");
		mAdapter.add(place);

	}

	@Override
	public void onLocationChanged(Location currentLocation) {

		// DONE - Handle location updates

        // Case 1 - there's no last location, so set the location to the
        // current location.
        if ( mLastLocationReading == null ) {
            mLastLocationReading = currentLocation;
            return;
        }

        // Case 2 - Current location is older than last location, so
        // ignore the current location by doing nothing.
        else if ( age(currentLocation) > age( mLastLocationReading )  ) {
            // Don't do anything, just ignore the current location by returning.
            return;
        }
        // Case 3 - Current location is newer then last location, so set
        // the location to the current location.
        else if ( age(currentLocation) < age( mLastLocationReading ) ) {
            mLastLocationReading = currentLocation;
            return;
        }
	}

	@Override
	public void onProviderDisabled(String provider) {
		// not implemented
	}

	@Override
	public void onProviderEnabled(String provider) {
		// not implemented
	}

	@Override
	public void onStatusChanged(String provider, int status, Bundle extras) {
		// not implemented
	}

	private long age(Location location) {
		return System.currentTimeMillis() - location.getTime();
	}

	@Override
	public boolean onCreateOptionsMenu(Menu menu) {
		MenuInflater inflater = getMenuInflater();
		inflater.inflate(R.menu.main, menu);
		return true;
	}

	@Override
	public boolean onOptionsItemSelected(MenuItem item) {
		switch (item.getItemId()) {
		case R.id.print_badges:
			ArrayList<PlaceRecord> currData = mAdapter.getList();
			for (int i = 0; i < currData.size(); i++) {
				log(currData.get(i).toString());
			}
			return true;
		case R.id.delete_badges:
			mAdapter.removeAllViews();
			return true;
		case R.id.place_one:
			mMockLocationProvider.pushLocation(37.422, -122.084);
			return true;
		case R.id.place_invalid:
			mMockLocationProvider.pushLocation(0, 0);
			return true;
		case R.id.place_two:
			mMockLocationProvider.pushLocation(38.996667, -76.9275);
			return true;
		default:
			return super.onOptionsItemSelected(item);
		}
	}

	private static void log(String msg) {
		try {
			Thread.sleep(500);
		} catch (InterruptedException e) {
			e.printStackTrace();
		}
		Log.i(TAG, msg);
	}

}
