(function($) {
  $(document).ready(function(){

    var images = [];
    var i = 0;
    Drupal.settings.backgroundslider.keys = [];
    Drupal.settings.backgroundslider.loaded = 1;
    var opacity = Drupal.settings.backgroundslider.settings.opacity;

    for (var key in Drupal.settings.backgroundslider.backgrounds){
      var background = Drupal.settings.backgroundslider.backgrounds[key];
      images[i] = background.image;
      Drupal.settings.backgroundslider.keys[i] = key;
      if (i == 0) {
        $.each(background.elements, function(index, value) {
          var color = getRgba(background.color, opacity);
          $(value).css('background-color', color);
        });
      }
      i = i + 1;
    };

    $('body').bgStretcher({
      images: images,
      imageWidth: Drupal.settings.backgroundslider.settings.width,
      imageHeight: Drupal.settings.backgroundslider.settings.height,
      resizeProportionally: true,
      nextSlideDelay: Drupal.settings.backgroundslider.settings.delay,
      slideShowSpeed: Drupal.settings.backgroundslider.settings.speed,
      transitionEffect: Drupal.settings.backgroundslider.settings.effect,
      sequenceMode: Drupal.settings.backgroundslider.settings.sequence,
      slideDirection: Drupal.settings.backgroundslider.settings.direction,
      startElementIndex: Drupal.settings.backgroundslider.settings.start,
      buttonPrev: '#bgstretcherPrev',
      buttonNext: '#bgstretcherNext',
      anchoring: 'left center',
      anchoringImg: 'left center',
      callbackfunction: callback
    });

  });

  function callback() {
    var index = Drupal.settings.backgroundslider.loaded;
    var key = Drupal.settings.backgroundslider.keys[index];
    //alert(key);
    var color = Drupal.settings.backgroundslider.backgrounds[key].color;
    var elements = Drupal.settings.backgroundslider.backgrounds[key].elements;
    var opacity = Drupal.settings.backgroundslider.settings.opacity;
    var rgbaColor = getRgba(color, opacity);
    $.each(elements, function(index, value) {
      $(value).animate({
        backgroundColor: rgbaColor,
      }, Drupal.settings.backgroundslider.settings.speed);
    });

    if (Drupal.settings.backgroundslider.loaded < i - 1) {
      Drupal.settings.backgroundslider.loaded = Drupal.settings.backgroundslider.loaded + 1;
    }
    else {
      Drupal.settings.backgroundslider.loaded = 0;
    }
  }

  function getRgba(hex, opa) {
    var r = parseInt(hex.substring(0,2),16);
    var g = parseInt(hex.substring(2,4),16);
    var b = parseInt(hex.substring(4,6),16);
    return 'rgba(' + r + ',' + g + ',' + b + ',' + opa + ')';
  }

})(jQuery);
