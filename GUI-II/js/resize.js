/*
    This function was found on the Image Map Resizer GitHub issues page.
    URL: https://github.com/davidjbradshaw/image-map-resizer/issues/35
*/
function __init_resize() {
    $('img[usemap]').each(function(e,index){
      var $this = $(this);
      var img = $(index)[0];
      var i_w = $this.width();
      var i_h = $this.height();
      var pic_real_width, pic_real_height;

            // HERE WE NEED TO SAVE IMG TO MEMORY TO CHECK IT'S
            // ORIGINAL SIZE
      $("<img/>")
        .attr("src", $(img).attr("src"))
        .load(function() {

          pic_real_width = this.width;
          pic_real_height = this.height;
          var procent_w = (i_w * 100) / pic_real_width;
          var procent_h = (i_h * 100) / pic_real_height;

          var map_id = $(img).attr('usemap');
          $(map_id).find('area').each(function(){
            var $area = $(this);

            var sc = $area.attr('sc');
            if(typeof sc !== typeof undefined && sc !== false){
              var coords = $(this).attr('sc');
            }else{
              var coords = $(this).attr('coords');
              $area.attr('sc',$area.attr('coords'));
            }

            var coords_array = coords.split(',');
            var coords_temp = new Array();        // NOT IMPORTANT ARRAY ;-)
            var coords_string = '';
            var counter = 0;

            $.each(coords_array,function(e,index){
              if(counter % 2 == 0){
                // Y Coord
                coords_temp.push(Math.round(index * (procent_h / 100)));
                coords_string += Math.round(index * (procent_h / 100))+',';
              }else{
                // X Coord
                coords_temp.push(Math.round(index * (procent_w / 100)));
                coords_string += Math.round(index * (procent_w / 100))+',';
              }

              counter++;
            });

            coords_string = coords_string.slice(0, -1);
            $area.attr('coords',coords_string);

                    // CUSTOM EVENT TRIGGER
                     //  I am using it for my own purposes but if You need it's here :-)
            $(document).trigger('resizeMap');

          });

        });
    });
 }