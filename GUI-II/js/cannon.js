/*
 *  This file is for the Bretton Woods Dynamic Ski Map
 *  It will pull in a JSON file and load up the open / closed trails onto
 *  an image displayed using HTML.
 *
 *  File created: 1/28/2016 12PM EST
 *   Last edited: 4/26/2016   7PM EST
 *    Created by: Jason Downing
 *
 */

/*
    Global color variables
    Red   = CLOSED
    Green = OPEN
*/
var open_color = "006600";
var closed_color = "A30002";

// JSON data for Cannon
var nov15_json = {
 "waterville_closed": [
    "Profile",
    "Taft Slalom",
    "Upper Ravine",
    "Skylight",
    "Upper Hardscrabble",
    "The Saddle",
    "Short Fuse",
    "Wicked Haahhd",
    "Middle Hardscrabble",
    "Upper Cannon",
    "Tramway",
    "Vista Way",
    "Kinsman Glade",
    "Baron's Run",
    "Cannonball",
    "Track Track",
    "Skyline",
    "Idiot's Delight",
    "Ridge Run",
    "Candyland",
    "Taft Training Slope",
    "North Slope",
    "Mittersill Lift Line",
    "TBD Trail",
    "Golden Birches Glade",
    "Way Back",
    "David's Detour",
    "Goat Path",
    "Big Link",
    "Lower Hardscrabble",
    "The Creek",
    "Amazon Glade",
    "Mushroom Glade",
    "MG Cut Thru",
    "Blue Ball",
    "Red Ball",
    "Turkey Trot",
    "Moose Alley",
    "Peregrine Parkway Glade",
    "Rabbit Path",
    "Coyote Crossing",
    "Fleitman Trail",
    "Deer Run",
    "Raven Ridge",
    "Huckerbrook",
    "Fox Trail",
    "Bear Paw",
    "Robin's Nest Glade",
    "Brookside",
    "Turnpike",
    "Stinky St.",
    "Turnpike Glade",
    "Snowmakers' Glade",
    "Lil Bertha",
    "Rocket",
    "Zoomer Lift Line",
    "Lakeside",
    "Zoomalanche",
    "Echo Woods Glade",
    "Paulie's Folly",
    "Avalanche",
    "Tram Cutback",
    "Skateway",
    "Banshee Cut-Thru",
    "Banshee",
    "Whiskey Towne",
    "Jasper's Hideaway",
    "Banshee Lift Line",
    "Banshee Glade",
    "Ride Around",
    "DJ's Tramline",
    "Lost Boy's Glade",
    "Gary's",
    "Zoomer"
  ],
  "waterville_open": [
    "Easy Link",
    "Missing Link",
    "Bypass",
    "Middle Cannon",
    "Middle Ravine",
    "Turnpike",
    "Spookie",
    "Lower Ravine",
    "Chute",
    "Gremlin",
    "Parkway",
    "Rock Garden",
    "Extension",
    "Lower Cannon",
    "Mickey's Margin",
    "Tossup Park",
    "Time Zone"
  ]
};

var dec15_json = {
  "waterville_closed": [
    "Candyland",
    "Taft Training Slope",
    "North Slope",
    "Mittersill Lift Line",
    "TBD Trail",
    "Golden Birches Glade",
    "Way Back",
    "David's Detour",
    "Mickey's Margin",
    "Gary's",
    "Tossup Park",
    "Time Zone",
    "Snowmakers' Glade",
    "Lil Bertha",
    "Rocket",
    "Zoomer Lift Line",
    "Lakeside",
    "Zoomalanche",
    "Echo Woods Glade",
    "Paulie's Folly",
    "Avalanche",
    "Tram Cutback",
    "Skateway",
    "Banshee Cut-Thru",
    "Banshee",
    "Whiskey Towne",
    "Jasper's Hideaway",
    "Banshee Lift Line",
    "Banshee Glade",
    "Ride Around",
    "DJ's Tramline",
    "Lost Boy's Glade",
    "Baron's Run",
    "Track Track",
    "Skyline",
    "Idiot's Delight",
    "Ridge Run",
    "Cannonball",
    "The Saddle",
    "Wicked Haahhd",
    "Middle Hardscrabble",
    "Zoomer",
    "Profile",
    "Taft Slalom",
    "Upper Ravine",
    "Skylight",
    "Upper Hardscrabble",
    "Short Fuse",
    "Upper Cannon",
    "Tramway",
    "Vista Way",
    "Kinsman Glade",
    "Amazon Glade",
    "Mushroom Glade",
    "MG Cut Thru"
  ],
  "waterville_open": [
    "Stinky St.",
    "Turnpike Glade",
    "Turnpike",
    "Spookie",
    "Lower Ravine",
    "Chute",
    "Gremlin",
    "Parkway",
    "Rock Garden",
    "Extension",
    "Lower Cannon",
    "Bypass",
    "Middle Cannon",
    "Easy Link",
    "Missing Link",
    "Goat Path",
    "Big Link",
    "Lower Hardscrabble",
    "The Creek",
    "Blue Ball",
    "Red Ball",
    "Turkey Trot",
    "Moose Alley",
    "Peregrine Parkway Glade",
    "Rabbit Path",
    "Coyote Crossing",
    "Fleitman Trail",
    "Deer Run",
    "Raven Ridge",
    "Huckerbrook",
    "Fox Trail",
    "Bear Paw",
    "Robin's Nest Glade",
    "Brookside",
    "Middle Ravine",
    "Turnpike"
  ]
};

var jan15_json = {
  "waterville_closed": [
    "Profile",
    "Taft Slalom",
    "Upper Ravine",
    "Skylight",
    "Upper Hardscrabble",
    "Short Fuse",
    "Upper Cannon",
    "Tramway",
    "Vista Way",
    "Kinsman Glade",
    "Amazon Glade",
    "Mushroom Glade",
    "MG Cut Thru",
    "Wicked Haahhd",
    "Middle Hardscrabble",
    "The Saddle",
    "Lost Boy's Glade"
  ],
  "waterville_open": [
    "The Creek",
    "Candyland",
    "Taft Training Slope",
    "North Slope",
    "Mittersill Lift Line",
    "TBD Trail",
    "Golden Birches Glade",
    "Way Back",
    "David's Detour",
    "Bypass",
    "Middle Cannon",
    "Easy Link",
    "Missing Link",
    "Goat Path",
    "Big Link",
    "Lower Hardscrabble",
    "Blue Ball",
    "Red Ball",
    "Turkey Trot",
    "Moose Alley",
    "Peregrine Parkway Glade",
    "Rabbit Path",
    "Coyote Crossing",
    "Fleitman Trail",
    "Deer Run",
    "Raven Ridge",
    "Huckerbrook",
    "Fox Trail",
    "Bear Paw",
    "Robin's Nest Glade",
    "Brookside",
    "Middle Ravine",
    "Turnpike",
    "Stinky St.",
    "Turnpike Glade",
    "Turnpike",
    "Spookie",
    "Lower Ravine",
    "Chute",
    "Gremlin",
    "Parkway",
    "Rock Garden",
    "Extension",
    "Lower Cannon",
    "Zoomer",
    "Mickey's Margin",
    "Gary's",
    "Tossup Park",
    "Time Zone",
    "Snowmakers' Glade",
    "Lil Bertha",
    "Rocket",
    "Zoomer Lift Line",
    "Lakeside",
    "Zoomalanche",
    "Echo Woods Glade",
    "Paulie's Folly",
    "Avalanche",
    "Tram Cutback",
    "Skateway",
    "Banshee Cut-Thru",
    "Banshee",
    "Whiskey Towne",
    "Jasper's Hideaway",
    "Banshee Lift Line",
    "Banshee Glade",
    "Ride Around",
    "DJ's Tramline",
    "Baron's Run",
    "Track Track",
    "Skyline",
    "Idiot's Delight",
    "Ridge Run",
    "Cannonball"
  ]
};

var feb15_json = {
  "waterville_closed": [

  ],
  "waterville_open": [
    "Profile",
    "Taft Slalom",
    "Upper Ravine",
    "Skylight",
    "Upper Hardscrabble",
    "The Saddle",
    "Short Fuse",
    "Wicked Haahhd",
    "Middle Hardscrabble",
    "Upper Cannon",
    "Tramway",
    "Vista Way",
    "Kinsman Glade",
    "Baron's Run",
    "Cannonball",
    "Track Track",
    "Skyline",
    "Idiot's Delight",
    "Ridge Run",
    "Candyland",
    "Taft Training Slope",
    "North Slope",
    "Mittersill Lift Line",
    "TBD Trail",
    "Golden Birches Glade",
    "Way Back",
    "David's Detour",
    "Bypass",
    "Middle Cannon",
    "Easy Link",
    "Missing Link",
    "Goat Path",
    "Big Link",
    "Lower Hardscrabble",
    "The Creek",
    "Amazon Glade",
    "Mushroom Glade",
    "MG Cut Thru",
    "Blue Ball",
    "Red Ball",
    "Turkey Trot",
    "Moose Alley",
    "Peregrine Parkway Glade",
    "Rabbit Path",
    "Coyote Crossing",
    "Fleitman Trail",
    "Deer Run",
    "Raven Ridge",
    "Huckerbrook",
    "Fox Trail",
    "Bear Paw",
    "Robin's Nest Glade",
    "Brookside",
    "Middle Ravine",
    "Turnpike",
    "Stinky St.",
    "Turnpike Glade",
    "Turnpike",
    "Spookie",
    "Lower Ravine",
    "Chute",
    "Gremlin",
    "Parkway",
    "Rock Garden",
    "Extension",
    "Lower Cannon",
    "Zoomer",
    "Mickey's Margin",
    "Gary's",
    "Tossup Park",
    "Time Zone",
    "Snowmakers' Glade",
    "Lil Bertha",
    "Rocket",
    "Zoomer Lift Line",
    "Lakeside",
    "Zoomalanche",
    "Echo Woods Glade",
    "Paulie's Folly",
    "Avalanche",
    "Tram Cutback",
    "Skateway",
    "Banshee Cut-Thru",
    "Banshee",
    "Whiskey Towne",
    "Jasper's Hideaway",
    "Banshee Lift Line",
    "Banshee Glade",
    "Ride Around",
    "DJ's Tramline",
    "Lost Boy's Glade"
  ]
};

var mar15_json = {
  "waterville_closed": [
    "Idiot's Delight",
    "Golden Birches Glade",
    "Kinsman Glade",
    "Wicked Haahhd",
    "Robin's Nest Glade",
    "Lost Boy's Glade"
  ],
  "waterville_open": [
    "Profile",
    "Taft Slalom",
    "Upper Ravine",
    "Skylight",
    "Upper Hardscrabble",
    "The Saddle",
    "Short Fuse",
    "Middle Hardscrabble",
    "Upper Cannon",
    "Tramway",
    "Vista Way",
    "Baron's Run",
    "Cannonball",
    "Track Track",
    "Skyline",
    "Ridge Run",
    "Candyland",
    "Taft Training Slope",
    "North Slope",
    "Mittersill Lift Line",
    "TBD Trail",
    "Way Back",
    "David's Detour",
    "Bypass",
    "Middle Cannon",
    "Easy Link",
    "Missing Link",
    "Goat Path",
    "Big Link",
    "Lower Hardscrabble",
    "The Creek",
    "Amazon Glade",
    "Mushroom Glade",
    "MG Cut Thru",
    "Blue Ball",
    "Red Ball",
    "Turkey Trot",
    "Moose Alley",
    "Peregrine Parkway Glade",
    "Rabbit Path",
    "Coyote Crossing",
    "Fleitman Trail",
    "Deer Run",
    "Raven Ridge",
    "Huckerbrook",
    "Fox Trail",
    "Bear Paw",
    "Brookside",
    "Middle Ravine",
    "Turnpike",
    "Stinky St.",
    "Turnpike Glade",
    "Turnpike",
    "Spookie",
    "Lower Ravine",
    "Chute",
    "Gremlin",
    "Parkway",
    "Rock Garden",
    "Extension",
    "Lower Cannon",
    "Zoomer",
    "Mickey's Margin",
    "Gary's",
    "Tossup Park",
    "Time Zone",
    "Snowmakers' Glade",
    "Lil Bertha",
    "Rocket",
    "Zoomer Lift Line",
    "Lakeside",
    "Zoomalanche",
    "Echo Woods Glade",
    "Paulie's Folly",
    "Avalanche",
    "Tram Cutback",
    "Skateway",
    "Banshee Cut-Thru",
    "Banshee",
    "Whiskey Towne",
    "Jasper's Hideaway",
    "Banshee Lift Line",
    "Banshee Glade",
    "Ride Around",
    "DJ's Tramline"
  ]
};

var apr15_json = {
  "waterville_closed": [
    "Profile",
    "Taft Slalom",
    "Upper Ravine",
    "Skylight",
    "Upper Hardscrabble",
    "Short Fuse",
    "Upper Cannon",
    "Tramway",
    "Vista Way",
    "Kinsman Glade",
    "Amazon Glade",
    "Mushroom Glade",
    "MG Cut Thru",
    "Wicked Haahhd",
    "Middle Hardscrabble",
    "The Saddle",
    "Idiot's Delight",
    "Golden Birches Glade",
    "Kinsman Glade",
    "Wicked Haahhd",
    "Robin's Nest Glade",
    "Lost Boy's Glade"
  ],
  "waterville_open": [
    "The Creek",
    "Candyland",
    "Taft Training Slope",
    "North Slope",
    "Mittersill Lift Line",
    "TBD Trail",
    "Golden Birches Glade",
    "Way Back",
    "David's Detour",
    "Bypass",
    "Middle Cannon",
    "Easy Link",
    "Missing Link",
    "Goat Path",
    "Big Link",
    "Lower Hardscrabble",
    "Blue Ball",
    "Red Ball",
    "Turkey Trot",
    "Moose Alley",
    "Peregrine Parkway Glade",
    "Rabbit Path",
    "Coyote Crossing",
    "Fleitman Trail",
    "Deer Run",
    "Raven Ridge",
    "Huckerbrook",
    "Fox Trail",
    "Bear Paw",
    "Robin's Nest Glade",
    "Brookside",
    "Middle Ravine",
    "Turnpike",
    "Stinky St.",
    "Turnpike Glade",
    "Turnpike",
    "Spookie",
    "Lower Ravine",
    "Chute",
    "Gremlin",
    "Parkway",
    "Rock Garden",
    "Extension",
    "Lower Cannon",
    "Zoomer",
    "Mickey's Margin",
    "Gary's",
    "Tossup Park",
    "Time Zone",
    "Snowmakers' Glade",
    "Lil Bertha",
    "Rocket",
    "Zoomer Lift Line",
    "Lakeside",
    "Zoomalanche",
    "Echo Woods Glade",
    "Paulie's Folly",
    "Avalanche",
    "Tram Cutback",
    "Skateway",
    "Banshee Cut-Thru",
    "Banshee",
    "Whiskey Towne",
    "Jasper's Hideaway",
    "Banshee Lift Line",
    "Banshee Glade",
    "Ride Around",
    "DJ's Tramline",
    "Baron's Run",
    "Track Track",
    "Skyline",
    "Idiot's Delight",
    "Ridge Run",
    "Cannonball"
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
  $('img[usemap]').rwdImageMaps();
  $('.map').maphilight().parent().addClass('center-map_cmt');

  // This is a total hack, but if it works, I'm happy.
  color_yellow();
  color_red();

});

// Change all the highlighting to yellow.
function color_yellow() {
  // This goes through and changes all the maphilight data "fillColor" properties
  // to "FFEA1C" which is the same yellow color I set as "default" for all areas.
  $("area").each(function(){
    $(this).data('maphilight', {"fillColor": open_color});
  });

  // Center the map using this helpful SO post
  // https://stackoverflow.com/questions/1760586/how-to-align-the-jquery-maphilight-to-center
  $('.map').maphilight().parent().addClass('center-map_cmt');
  $('img[usemap]').rwdImageMaps();

  return true;
}

// Change all the highlighting to red.
function color_red() {
  // This goes through and changes all the maphilight data "fillColor" properties
  // to "A30002" which is a red color.
  $("area").each(function(){
    $(this).data('maphilight', {"fillColor": closed_color});
  });

  // Center the map using this helpful SO post
  // https://stackoverflow.com/questions/1760586/how-to-align-the-jquery-maphilight-to-center
  $('.map').maphilight().parent().addClass('center-map_cmt');
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
  $('.map').maphilight().parent().addClass('center-map_bw');
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
