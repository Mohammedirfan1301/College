/*
 *  This file is for the Bretton Woods Dynamic Ski Map
 *  It will pull in a JSON file and load up the open / closed trails onto
 *  an image displayed using HTML.
 *
 *  File created: 1/28/2016 12:30PM EST
 *   Last edited: 1/28/2016 12:30PM EST
 *    Created by: Jason Downing
 *
 */
var ski_data;

/*
    Global color variables
    Red   = CLOSED
    Green = OPEN
*/
var open_color = "006600";
var closed_color = "A30002";

// JSON for Loon.
var nov15_json = {
  "waterville_closed": [
    "#flume",
    "#walkingboss",
    "#brookway",
    "#sunset",
    "#haulback",
    "#bearclaw",
    "#exodus",
    "#upperrumrunner",
    "#grandjunction",
    "#middleblacks",
    "#upperpickedrock",
    "#flyingfox",
    "#mikesway",
    "#loonmountainpark",
    "#picoon",
    "#middleblue",
    "#littlesister",
    "#lowerbearclaw",
    "smalltrails",
    "#coolidge",
    "#lowerrumrunner",
    "#scaler",
    "#boomrun",
    "#twitcher",
    "#jobber",
    "#ripsaw",
    "#cruiser",
    "#undercut",
    "#bosswoods"
  ],
  "waterville_open": [
    "#snubber",
    "#speakeasy",
    "#lowerpickrock",
    "#northstar",
    "#rampasture",
    "#blueox"
  ]
};

var dec15_json = {
  "waterville_closed": [
    "#flume",
    "#walkingboss",
    "#brookway",
    "#sunset",
    "#haulback",
    "#bearclaw",
    "#exodus",
    "#flyingfox",
    "#mikesway",
    "#loonmountainpark",
    "#picoon",
    "#middleblue",
    "#littlesister",
    "#lowerbearclaw",
    "smalltrails",
    "#coolidge",
    "#lowerrumrunner",
    "#scaler",
    "#boomrun",
    "#twitcher",
    "#jobber",
    "#ripsaw",
    "#cruiser",
    "#undercut",
    "#bosswoods"
  ],
  "waterville_open": [
    "#snubber",
    "#upperrumrunner",
    "#grandjunction",
    "#middleblacks",
    "#upperpickedrock",
    "#speakeasy",
    "#lowerpickrock",
    "#northstar",
    "#rampasture",
    "#blueox"
  ]
};

var jan15_json = {
  "waterville_closed": [
    "#flume",
    "#walkingboss",
    "#brookway",
    "#sunset",
    "#haulback",
    "#bearclaw",
    "#exodus",
    "#flyingfox",
    "#mikesway",
    "smalltrails",
    "#boomrun",
    "#twitcher",
    "#jobber",
    "#ripsaw",
    "#cruiser",
    "#undercut",
    "#bosswoods"
  ],
  "waterville_open": [
    "#snubber",
    "#scaler",
    "#coolidge",
    "#lowerrumrunner",
    "#loonmountainpark",
    "#picoon",
    "#middleblue",
    "#littlesister",
    "#lowerbearclaw",
    "#upperrumrunner",
    "#grandjunction",
    "#middleblacks",
    "#upperpickedrock",
    "#speakeasy",
    "#lowerpickrock",
    "#northstar",
    "#rampasture",
    "#blueox"
  ]
};

var feb15_json = {
  "waterville_closed": [
  ],
  "waterville_open": [
    "#flume",
    "#walkingboss",
    "#brookway",
    "#sunset",
    "#haulback",
    "#bearclaw",
    "#exodus",
    "#speakeasy",
    "#snubber",
    "#upperrumrunner",
    "#grandjunction",
    "#middleblacks",
    "#upperpickedrock",
    "#flyingfox",
    "#mikesway",
    "#northstar",
    "#rampasture",
    "#blueox",
    "#lowerpickrock",
    "#loonmountainpark",
    "#picoon",
    "#middleblue",
    "#littlesister",
    "#lowerbearclaw",
    "smalltrails",
    "#coolidge",
    "#lowerrumrunner",
    "#scaler",
    "#boomrun",
    "#twitcher",
    "#jobber",
    "#ripsaw",
    "#cruiser",
    "#undercut",
    "#bosswoods"
  ]
};

var mar15_json = {
  "waterville_closed": [
    "#twitcher",
    "#jobber",
    "#ripsaw",
    "#undercut",
    "#bosswoods"
  ],
  "waterville_open": [
    "#cruiser",
    "#flume",
    "#walkingboss",
    "#brookway",
    "#sunset",
    "#haulback",
    "#bearclaw",
    "#exodus",
    "#speakeasy",
    "#snubber",
    "#upperrumrunner",
    "#grandjunction",
    "#middleblacks",
    "#upperpickedrock",
    "#flyingfox",
    "#mikesway",
    "#northstar",
    "#rampasture",
    "#blueox",
    "#lowerpickrock",
    "#loonmountainpark",
    "#picoon",
    "#middleblue",
    "#littlesister",
    "#lowerbearclaw",
    "smalltrails",
    "#coolidge",
    "#lowerrumrunner",
    "#scaler",
    "#boomrun"
  ]
};

var apr15_json = {
  "waterville_closed": [
    "#twitcher",
    "#jobber",
    "#ripsaw",
    "#undercut",
    "#bosswoods",
    "#walkingboss",
    "#middleblacks",
  ],
  "waterville_open": [
    "#cruiser",
    "#flume",
    "#brookway",
    "#sunset",
    "#haulback",
    "#bearclaw",
    "#exodus",
    "#speakeasy",
    "#snubber",
    "#upperrumrunner",
    "#grandjunction",
    "#upperpickedrock",
    "#flyingfox",
    "#mikesway",
    "#northstar",
    "#rampasture",
    "#blueox",
    "#lowerpickrock",
    "#loonmountainpark",
    "#picoon",
    "#middleblue",
    "#littlesister",
    "#lowerbearclaw",
    "smalltrails",
    "#coolidge",
    "#lowerrumrunner",
    "#scaler",
    "#boomrun"
  ]
};

$(document).ready(function() {
  /*  This is from the maphilight docs, and has been modified to fix some bugs with
      the highlighting.
      The alwaysOn and neverOn attributes have been modified to fix issues on the first
      page load. They are noted below in comments.
  */
  $.fn.maphilight.defaults = {
    fill: true,
    fillColor: closed_color,
    fillOpacity: 0.5,
    stroke: false,
    strokeColor: '000000',
    strokeOpacity: 1,
    strokeWidth: 1,
    fade: false,
    alwaysOn: false,        // This is set to "False" on page load to prevent the highlighting from showing up messed up.
    neverOn: true,          // This is set to "True" on page load so no highlighting shows up at all until a button is clicked.
    groupBy: false,
    wrapClass: true,
    shadow: false,
    shadowX: 0,
    shadowY: 0,
    shadowRadius: 6,
    shadowColor: '000000',
    shadowOpacity: 0.8,
    shadowPosition: 'outside',
    shadowFrom: false
  }

  // Center the map using this helpful SO post
  // https://stackoverflow.com/questions/1760586/how-to-align-the-jquery-maphilight-to-center
  $('.map').maphilight().parent().addClass('center-map_loon');
  $('img[usemap]').rwdImageMaps();

  // This is a total hack, but if it works, I'm happy.
  color_yellow();
  color_red();

});

// Change all the highlighting to yellow.
function color_yellow() {
  var trails_on = [];

  // This goes through and changes all the maphilight data "fillColor" properties
  // to "FFEA1C" which is the same yellow color I set as "default" for all areas.
  $("area").each(function(){
    console.log("CHANGING COLORS to YELLOW");
    $(this).data('maphilight', {"fillColor": open_color});
    trails_on.push($(this).attr("alt"));
  });

  // All trails
  console.log(trails_on);

  // Center the map using this helpful SO post
  // https://stackoverflow.com/questions/1760586/how-to-align-the-jquery-maphilight-to-center
  $('.map').maphilight().parent().addClass('center-map_loon');
  $('img[usemap]').rwdImageMaps();

  return true;
}

// Change all the highlighting to red.
function color_red() {
  // This goes through and changes all the maphilight data "fillColor" properties
  // to "A30002" which is a red color.
  $("area").each(function(){
    console.log("CHANGING COLORS to RED");
    $(this).data('maphilight', {"fillColor": closed_color});
  });

  // Center the map using this helpful SO post
  // https://stackoverflow.com/questions/1760586/how-to-align-the-jquery-maphilight-to-center
  $('.map').maphilight().parent().addClass('center-map_loon');
  $('img[usemap]').rwdImageMaps();

  return true;
}

// Update map function.
// Given a JSON file name, it will update the waterville valley page.
function update_map(filename) {
  /*  This is from the maphilight docs, and has been modified to fix some bugs with
      the highlighting.
      The alwaysOn and neverOn attributes have been modified to fix issues on the first
      page load. They are noted below in comments. They get reset to default values here
      so that the highlighting will work again when a user clicks on one of the date buttons.
  */
  $.fn.maphilight.defaults = {
    fill: true,
    fillColor: closed_color,
    fillOpacity: 0.5,
    stroke: false,
    strokeColor: '000000',
    strokeOpacity: 1,
    strokeWidth: 1,
    fade: false,
    alwaysOn: true,       // This gets set to true so that the highlighting will work again.
    neverOn: false,       // This gets set to false so that the highlighting will show up again.
    groupBy: false,
    wrapClass: true,
    shadow: false,
    shadowX: 0,
    shadowY: 0,
    shadowRadius: 6,
    shadowColor: '000000',
    shadowOpacity: 0.8,
    shadowPosition: 'outside',
    shadowFrom: false
  }

  // List of trails open / closed.
  var open_trails = filename.waterville_open;
  var closed_trails = filename.waterville_closed;

  // Open Trails
  $("area").each(function(){
    for (trail in open_trails) {
      var compare = open_trails[trail];

      if(compare == $(this).attr("alt")) {
        $(this).data('maphilight', {"fillColor":open_color});
      }
    }
  });

  // Closed Trails
  $("area").each(function(){
    for (trail in closed_trails) {
      var compare = closed_trails[trail];

      if(compare == $(this).attr("alt")) {
        $(this).data('maphilight', {"fillColor":closed_color});
      }
    }
  });

  // Must call this to update the map!
  // Center the map using this helpful SO post
  // https://stackoverflow.com/questions/1760586/how-to-align-the-jquery-maphilight-to-center
  $('.map').maphilight().parent().addClass('center-map_loon');
}


// Update the sidebar with a list of trails based on filename given.
// IDEA: ADD SCROLL WHEEL.
function update_sidebar(filename) {
  // Empty IDs
  $( "#open_trails" ).empty();
  $( "#closed_trails" ).empty();

  // Add open trails.
  for(var open in filename.waterville_open) {
    $("#open_trails").append("<div>" + filename.waterville_open[open] + "</div>");
  }

  // Add closed trails.
  for(var closed in filename.waterville_closed) {
    $("#closed_trails").append("<div>" + filename.waterville_closed[closed] + "</div>");
  }
}


// This will be a demo function to change the map we have working,
// with fake data.
function change_day(date) {
  // Change date based on input.
  if(date == "nov15") {
    update_map(nov15_json);
    update_sidebar(nov15_json);

    return true;
  }

  if(date == "dec15") {
    update_map(dec15_json);
    update_sidebar(dec15_json);

    return true;
  }

  if(date == "jan15") {
    update_map(jan15_json);
    update_sidebar(jan15_json);

    return true;
  }

  if(date == "feb15") {
    update_map(feb15_json);
    update_sidebar(feb15_json);

    return true;
  }

  if(date == "mar15") {
    update_map(mar15_json);
    update_sidebar(mar15_json);

    return true;
  }

  if(date == "apr15") {
    update_map(apr15_json);
    update_sidebar(apr15_json);

    return true;
  }

  if(date == "may15") {
    update_map(nov15_json);   // Nov15 because all closed.
    update_sidebar(nov15_json);

    return true;
  }

  else {
    console.log("Error, given invalid date.\n");
  }
}
