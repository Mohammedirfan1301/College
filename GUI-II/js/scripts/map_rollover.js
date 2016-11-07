
jQuery(document).ready(function($){
	$('img[usemap]').maphilight();
	$('img[usemap]').rwdImageMaps();
});


jQuery(window).bind('resize', function(e)
{
    window.resizeEvt;
    jQuery(window).resize(function()
    {
        clearTimeout(window.resizeEvt);
        window.resizeEvt = setTimeout(function()
        {
            jQuery('img[usemap]').maphilight();
        }, 250);
    });
});