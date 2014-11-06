
CONTENTS OF THIS FILE
---------------------

 * Introduction
 * Installation
 * Usage


INTRODUCTION
------------

Developer: Raphael DŸrst <raphael.duerst@innoveto.com>

The Background Slider module uses the bgstretcher JavaScript library to display
a fullscreen background slideshow on your website.


INSTALLATION
------------

1. This module requires the the following modules.
    - Image
    - Entity API
    - Libraries API
   Make sure that these modules are enabled.

2. Copy this backgroundslider/ directory to your sites/SITENAME/modules
   directory.

3. Download the bgstretcher library.
http://www.ajaxblender.com/script-sources/bgstretcher/download/bgstretcher.zip

4. Copy the bgstretcher library to sites/all/libraries
   Make sure the folder has the name bgstretcher/

5. Enable the module in admin/modules

6. Configure the module in admin/config/user-interface/backgroundslider


USAGE
-----

Backgrounds can be managed in admin/appearance/background.

You can also choose a color for every background. Every element listed in the
configuration of the background will have this color applied to.

Make sure, that all your background images have the same size (or at least the
same aspect ratio).

You need to define the size of your images in the module configuration.
