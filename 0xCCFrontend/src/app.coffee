global.jQuery = global.$ = $ = require 'jquery'
$(document).ready ->
  $('.collapsible').collapsible(
    accordion : false
  )
