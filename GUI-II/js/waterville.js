/*
 *  This file is for the Waterville Valley Dynamic Ski Map
 *  It will pull in a JSON file and load up the open / closed trails onto
 *  an image displayed using HTML.
 *
 *  File created: 1/28/2016 12:30PM EST
 *   Last edited: 4/25/2016 12:30PM EST
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

/******************************************************************************
    This date has been FAKED to work for the demo.
    Since the ski season has ended, we had to resort to faked data.
*/
var nov15_json = {
  "waterville_closed": [
    "Sun Run",
    "Ciao",
    "Tree Line",
    "Ruthies Run",
    "Scramble",
    "Tree Line",
    "Main Street",
    "True Grit",
    "Gema",
    "Oblivion",
    "Palmers Way",
    "Bail Out",
    "Upper Bobbys",
    "Lower Bobby's Run",
    "Psyched Out",
    "White Caps",
    "Terrys Trail",
    "And Tyler Too",
    "Tippecanoe",
    "Tangent",
    "Sidewinder",
    "Grimes Way",
    "Periphery",
    "Lower Tippecanoe",
    "Boneyard",
    "Siegel Street",
    "Old Tecumseh",
    "Lower Periphery - FT",
    "Sel's Choice",
    "Lower Sel's Choice",
    "Tommy's World Cup Run - FT",
    "The Chute",
    "Psyched ",
    "Utter Abandon - FT",
    "Lower White Caps - FT",
    "Mini Pipe",
    "Exhibition - FT",
    "The Pasture",
    "Kinderpark Lift**For lessons only, closed to the public.\n",
    "South Street",
    "Stillness - FT",
    "Lower Stillness",
    "No Grit",
    "Baseway",
    "Kinderpark Lift**For lessons only, closed to the public.\n",
    "Exhibition"
  ],
  "waterville_open": [
    "Upper Valley Run",
    "Valley Run",
    "Rock Island",
    "Leroy's Loop",
    "Revelation",
    "Stemtation - FT"
  ]
};

var dec15_json = {
  "waterville_closed": [
    "Tree Line",
    "Ruthies Run",
    "Scramble",
    "Tree Line",
    "Main Street",
    "True Grit",
    "Gema",
    "Palmers Way",
    "Bail Out",
    "Upper Bobbys",
    "Lower Bobby's Run",
    "Psyched Out",
    "White Caps",
    "Terrys Trail",
    "And Tyler Too",
    "Tippecanoe",
    "Lower Tippecanoe",
    "Tangent",
    "Sidewinder",
    "Grimes Way",
    "Periphery",
    "Boneyard",
    "Siegel Street",
    "Old Tecumseh",
    "Lower Periphery - FT",
    "Sel's Choice",
    "Lower Sel's Choice",
    "Tommy's World Cup Run - FT",
    "The Chute",
    "Psyched ",
    "Utter Abandon - FT",
    "Lower White Caps - FT",
    "Mini Pipe",
    "Exhibition - FT",
    "The Pasture"
  ],
  "waterville_open": [
    "Kinderpark Lift**For lessons only, closed to the public.\n",
    "South Street",
    "Oblivion",
    "Sun Run",
    "Ciao",
    "Upper Valley Run",
    "Valley Run",
    "Rock Island",
    "Leroy's Loop",
    "Revelation",
    "Stemtation - FT",
    "Stillness - FT",
    "Lower Stillness",
    "No Grit",
    "Baseway",
    "Kinderpark Lift**For lessons only, closed to the public.\n",
    "Exhibition"
  ]
};

var jan15_json = {
  "waterville_closed": [
    "Tree Line",
    "Ruthies Run",
    "Scramble",
    "Tree Line",
    "Main Street",
    "True Grit",
    "Palmers Way",
    "Bail Out",
    "Upper Bobbys",
    "Lower Bobby's Run",
    "Psyched Out",
    "White Caps",
    "Terrys Trail",
    "Tangent",
    "Sidewinder",
    "Grimes Way",
    "Periphery",
    "Boneyard",
    "Siegel Street",
    "Old Tecumseh",
    "Sel's Choice",
    "Lower Sel's Choice",
    "Tommy's World Cup Run - FT",
    "The Chute",
    "Psyched ",
    "Utter Abandon - FT",
    "Lower White Caps - FT"
  ],
  "waterville_open": [
    "Exhibition - FT",
    "The Pasture",
    "Mini Pipe",
    "Lower Periphery - FT",
    "And Tyler Too",
    "Tippecanoe",
    "Lower Tippecanoe",
    "Gema",
    "Kinderpark Lift**For lessons only, closed to the public.\n",
    "South Street",
    "Oblivion",
    "Sun Run",
    "Ciao",
    "Upper Valley Run",
    "Valley Run",
    "Rock Island",
    "Leroy's Loop",
    "Revelation",
    "Stemtation - FT",
    "Stillness - FT",
    "Lower Stillness",
    "No Grit",
    "Baseway",
    "Kinderpark Lift**For lessons only, closed to the public.\n",
    "Exhibition"
  ]
};

var feb15_json = {
  "waterville_closed": [
  ],
  "waterville_open": [
    "Sun Run",
    "Ciao",
    "Tree Line",
    "Ruthies Run",
    "Scramble",
    "Tree Line",
    "Main Street",
    "True Grit",
    "Gema",
    "Oblivion",
    "Palmers Way",
    "Bail Out",
    "Upper Bobbys",
    "Lower Bobby's Run",
    "Psyched Out",
    "White Caps",
    "Terrys Trail",
    "And Tyler Too",
    "Tippecanoe",
    "Tangent",
    "Sidewinder",
    "Grimes Way",
    "Periphery",
    "Lower Tippecanoe",
    "Boneyard",
    "Siegel Street",
    "Old Tecumseh",
    "Lower Periphery - FT",
    "Sel's Choice",
    "Lower Sel's Choice",
    "Tommy's World Cup Run - FT",
    "The Chute",
    "Psyched ",
    "Utter Abandon - FT",
    "Lower White Caps - FT",
    "Mini Pipe",
    "Exhibition - FT",
    "The Pasture",
    "Kinderpark Lift**For lessons only, closed to the public.\n",
    "Upper Valley Run",
    "Rock Island",
    "Valley Run",
    "South Street",
    "Stillness - FT",
    "Lower Stillness",
    "No Grit",
    "Leroy's Loop",
    "Revelation",
    "Stemtation - FT",
    "Baseway",
    "Kinderpark Lift**For lessons only, closed to the public.\n",
    "Exhibition"
  ]
};

var mar15_json = {
  "waterville_closed": [
    "Exhibition Poma",
    "Boneyard",
    "Lower Bobby's Run",
    "Closed"
  ],
  "waterville_open": [
    "Psyched ",
    "Kinderpark Lift**For lessons only, closed to the public.\n",
    "The Pasture",
    "Baseway",
    "Kinder Park",
    "Leroy's Loop",
    "Revelation",
    "Stemtation",
    "Valley Run",
    "Main Street",
    "Ruthies Run",
    "Scramble",
    "Lower Stillness",
    "Rock Island",
    "Stillness",
    "And Tyler Too",
    "Bail Out",
    "Grimes Way",
    "Lower Periphery",
    "Lower Tippecanoe",
    "Lower White Caps",
    "No Grit",
    "Oblivion",
    "Old Tecumseh",
    "Palmers Way",
    "Periphery",
    "Higher Ground",
    "Sidewinder",
    "Siegel Street",
    "Sun Run",
    "Tangent",
    "Terrys Trail",
    "Tippecanoe",
    "Tree Line",
    "Upper Bobbys",
    "Upper Valley Run",
    "White Caps",
    "Psyched Out",
    "South Street",
    "Ciao",
    "Gema",
    "Lower Sel's Choice",
    "Psyched",
    "Sel's Choice",
    "The Chute",
    "Tommy's World Cup Run",
    "True Grit",
    "Utter Abandon",
    "Exhibition",
    "WV Progression Park",
    "Exhibition",
    "South Street",
    "Open",
    "Stillness - FT",
    "Tommy's World Cup Run - FT"
  ]
};

var apr15_json = {
  "waterville_closed": [
    "Exhibition Poma",
    "Boneyard",
    "Lower Bobby's Run",
    "Closed",
    "True Grit",
    "Gema",
    "Ciao"
  ],
  "waterville_open": [
    "Psyched ",
    "Kinderpark Lift**For lessons only, closed to the public.\n",
    "The Pasture",
    "Baseway",
    "Kinder Park",
    "Leroy's Loop",
    "Revelation",
    "Stemtation",
    "Valley Run",
    "Main Street",
    "Ruthies Run",
    "Scramble",
    "Lower Stillness",
    "Rock Island",
    "Stillness",
    "And Tyler Too",
    "Bail Out",
    "Grimes Way",
    "Lower Periphery",
    "Lower Tippecanoe",
    "Lower White Caps",
    "No Grit",
    "Oblivion",
    "Old Tecumseh",
    "Palmers Way",
    "Periphery",
    "Higher Ground",
    "Sidewinder",
    "Siegel Street",
    "Sun Run",
    "Tangent",
    "Terrys Trail",
    "Tippecanoe",
    "Tree Line",
    "Upper Bobbys",
    "Upper Valley Run",
    "White Caps",
    "Psyched Out",
    "South Street",
    "Lower Sel's Choice",
    "Psyched",
    "Sel's Choice",
    "The Chute",
    "Tommy's World Cup Run",
    "Utter Abandon",
    "Exhibition",
    "WV Progression Park",
    "Exhibition",
    "South Street",
    "Open",
    "Stillness - FT",
    "Tommy's World Cup Run - FT"
  ]
};

/*
    This function gets run on page load, and it sets up the defaults for the
    map highlighting.
*/
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
  $('.map').maphilight().parent().addClass('center-map');

  $('img[usemap]').rwdImageMaps();

  // This is a total hack in order to fix the highlighting.
  // Not sure how this works, but calling the color functions seems to make
  // the highlighting work properly.
  color_yellow();
  color_red();
});

// Change all the highlighting to GREEN.
// This functions name should be changed.
function color_yellow() {
  // This goes through and changes all the maphilight data "fillColor" properties
  // to "006600" which is the same yellow color I set as "default" for all areas.
  $("area").each(function(){
    $(this).data('maphilight', {"fillColor":open_color});
  });

  // Must call this to update the map!
  // Center the map using this helpful SO post
  // https://stackoverflow.com/questions/1760586/how-to-align-the-jquery-maphilight-to-center
  $('.map').maphilight().parent().addClass('center-map');

  return true;
}

// Change all the highlighting to red.
function color_red() {
  // This goes through and changes all the maphilight data "fillColor" properties
  // to "A30002" which is a red color.
  $("area").each(function(){
    $(this).data('maphilight', {"fillColor":closed_color});
  });

  // Must call this to update the map!
  // Center the map using this helpful SO post
  // https://stackoverflow.com/questions/1760586/how-to-align-the-jquery-maphilight-to-center
  $('.map').maphilight().parent().addClass('center-map');

  return true;
}

// Change the highlighting given a list of trails.
function color_list() {

  // List of trails open / closed.
  var open_trails = ski_data.waterville_open;
  var closed_trails = ski_data.waterville_closed;

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
  $('.map').maphilight().parent().addClass('center-map');

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
  $('.map').maphilight().parent().addClass('center-map');
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
