package course.labs.activitylab;

import android.app.Activity;
import android.os.Bundle;
import android.util.Log;
import android.view.View;
import android.view.View.OnClickListener;
import android.widget.Button;
import android.widget.TextView;

public class ActivityTwo extends Activity {

	private static final String RESTART_KEY = "restart";
	private static final String RESUME_KEY = "resume";
	private static final String START_KEY = "start";
	private static final String CREATE_KEY = "create";

	// String for LogCat documentation
	private final static String TAG = "Lab-ActivityTwo";

	// Lifecycle counters
	// Create counter variables for onCreate(), onRestart(), onStart() and
	// onResume(), called mCreate, etc.
	// You will need to increment these variables' values when their
	// corresponding lifecycle methods get called
    private int mCreate = 0, mRestart = 0, mStart = 0, mResume = 0;


	// Create variables for each of the TextViews, called
    // mTvCreate, etc.
    private TextView mTvCreate, mTvRestart, mTvStart, mTvResume;

	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		setContentView(R.layout.activity_two);

		// Assign the appropriate TextViews to the TextView variables
		// Hint: Access the TextView by calling Activity's findViewById()
		// textView1 = (TextView) findViewById(R.id.textView1);

        mTvCreate   = (TextView) findViewById(R.id.create);
        mTvStart    = (TextView) findViewById(R.id.start);
        mTvResume   = (TextView) findViewById(R.id.resume);
        mTvRestart  = (TextView) findViewById(R.id.restart);

		Button closeButton = (Button) findViewById(R.id.bClose); 
		closeButton.setOnClickListener(new OnClickListener() {

			@Override
			public void onClick(View v) {

				// This function closes Activity Two
				// Hint: use Context's finish() method
                finish();
			}
		});

		// Check for previously saved state
		if (savedInstanceState != null) {

			// Restore value of counters from saved state
			// Only need 4 lines of code, one for every count variable
            mCreate = savedInstanceState.getInt(CREATE_KEY);
            mStart = savedInstanceState.getInt(START_KEY);
            mResume = savedInstanceState.getInt(RESUME_KEY);
            mRestart = savedInstanceState.getInt(RESTART_KEY);
		}

		// Emit LogCat message
        Log.i(TAG, "onCreate() called - activity created.");

		// Update the appropriate count variable
		// Update the user interface via the displayCounts() method
        mCreate++;
        displayCounts();
	}

	// Lifecycle callback methods overrides

	@Override
	public void onStart() {
		super.onStart();

		// Emit LogCat message
        Log.i(TAG, "onStart() called - activity started.");

		// Update the appropriate count variable
		// Update the user interface
        mStart++;
        displayCounts();
	}

	@Override
	public void onResume() {
		super.onResume();

		// Emit LogCat message
        Log.i(TAG, "onResume() called - activity resumed.");

		// Update the appropriate count variable
		// Update the user interface
        mResume++;
        displayCounts();
	}

	@Override
	public void onPause() {
		super.onPause();

		// Emit LogCat message
        Log.i(TAG, "onPause() called - activity paused.");
	}

	@Override
	public void onStop() {
		super.onStop();

		// Emit LogCat message
        Log.i(TAG, "onStop() called - activity stopped.");
	}

	@Override
	public void onRestart() {
		super.onRestart();

		// Emit LogCat message
        Log.i(TAG, "onRestart() called - activity restarted.");

		// Update the appropriate count variable
		// Update the user interface
        mRestart++;
        displayCounts();
	}

	@Override
	public void onDestroy() {
		super.onDestroy();

		// Emit LogCat message
        Log.i(TAG, "onDestroy() called - activity destroyed.");
	}

	@Override
	public void onSaveInstanceState(Bundle savedInstanceState) {

		// Save counter state information with a collection of key-value pairs
		// 4 lines of code, one for every count variable
        // Saves the state for the next time the app is run
        savedInstanceState.putInt(CREATE_KEY, mCreate);
        savedInstanceState.putInt(START_KEY, mStart);
        savedInstanceState.putInt(RESUME_KEY, mResume);
        savedInstanceState.putInt(RESTART_KEY, mRestart);
	}

	// Updates the displayed counters
	public void displayCounts() {

        // Display the counts
		mTvCreate.setText("onCreate() calls: " + mCreate);
		mTvStart.setText("onStart() calls: " + mStart);
		mTvResume.setText("onResume() calls: " + mResume);
		mTvRestart.setText("onRestart() calls: " + mRestart);
	
	}
}
