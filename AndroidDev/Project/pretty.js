function initRichMarker() {
  function RichMarker(opt_options) {
    var options = opt_options || {};
    this.ready_ = !1, this.dragging_ = !1, void 0 == opt_options.visible && (opt_options.visible = !0), void 0 == opt_options.shadow && (opt_options.shadow = "7px -3px 5px rgba(88,88,88,0.7)"), void 0 == opt_options.anchor && (opt_options.anchor = RichMarkerPosition.BOTTOM), this.setValues(options)
  }
  RichMarker.prototype = new google.maps.OverlayView, window.RichMarker = RichMarker, RichMarker.prototype.getVisible = function() {
    return this.get("visible")
  }, RichMarker.prototype.getVisible = RichMarker.prototype.getVisible, RichMarker.prototype.setVisible = function(visible) {
    this.set("visible", visible)
  }, RichMarker.prototype.setVisible = RichMarker.prototype.setVisible, RichMarker.prototype.visible_changed = function() {
    this.ready_ && (this.markerWrapper_.style.display = this.getVisible() ? "" : "none", this.draw())
  }, RichMarker.prototype.visible_changed = RichMarker.prototype.visible_changed, RichMarker.prototype.setFlat = function(flat) {
    this.set("flat", !!flat)
  }, RichMarker.prototype.setFlat = RichMarker.prototype.setFlat, RichMarker.prototype.getFlat = function() {
    return this.get("flat")
  }, RichMarker.prototype.getFlat = RichMarker.prototype.getFlat, RichMarker.prototype.getWidth = function() {
    return this.get("width")
  }, RichMarker.prototype.getWidth = RichMarker.prototype.getWidth, RichMarker.prototype.getHeight = function() {
    return this.get("height")
  }, RichMarker.prototype.getHeight = RichMarker.prototype.getHeight, RichMarker.prototype.setShadow = function(shadow) {
    this.set("shadow", shadow), this.flat_changed()
  }, RichMarker.prototype.setShadow = RichMarker.prototype.setShadow, RichMarker.prototype.getShadow = function() {
    return this.get("shadow")
  }, RichMarker.prototype.getShadow = RichMarker.prototype.getShadow, RichMarker.prototype.flat_changed = function() {
    this.ready_ && (this.markerWrapper_.style.boxShadow = this.markerWrapper_.style.webkitBoxShadow = this.markerWrapper_.style.MozBoxShadow = this.getFlat() ? "" : this.getShadow())
  }, RichMarker.prototype.flat_changed = RichMarker.prototype.flat_changed, RichMarker.prototype.setZIndex = function(index) {
    this.set("zIndex", index)
  }, RichMarker.prototype.setZIndex = RichMarker.prototype.setZIndex, RichMarker.prototype.getZIndex = function() {
    return this.get("zIndex")
  }, RichMarker.prototype.getZIndex = RichMarker.prototype.getZIndex, RichMarker.prototype.zIndex_changed = function() {
    this.getZIndex() && this.ready_ && (this.markerWrapper_.style.zIndex = this.getZIndex())
  }, RichMarker.prototype.zIndex_changed = RichMarker.prototype.zIndex_changed, RichMarker.prototype.getDraggable = function() {
    return this.get("draggable")
  }, RichMarker.prototype.getDraggable = RichMarker.prototype.getDraggable, RichMarker.prototype.getTitle = function() {
    return this.get("title")
  }, RichMarker.prototype.getTitle = RichMarker.prototype.getTitle, RichMarker.prototype.setDraggable = function(draggable) {
    this.set("draggable", !!draggable)
  }, RichMarker.prototype.setDraggable = RichMarker.prototype.setDraggable, RichMarker.prototype.setTitle = function(title_string) {
    this.set("title", title_string)
  }, RichMarker.prototype.setTitle = RichMarker.prototype.setTitle, RichMarker.prototype.draggable_changed = function() {
    this.ready_ && (this.getDraggable() ? this.addDragging_(this.markerWrapper_) : this.removeDragListeners_())
  }, RichMarker.prototype.draggable_changed = RichMarker.prototype.draggable_changed, RichMarker.prototype.getPosition = function() {
    return this.get("position")
  }, RichMarker.prototype.getPosition = RichMarker.prototype.getPosition, RichMarker.prototype.setPosition = function(position) {
    this.set("position", position)
  }, RichMarker.prototype.setPosition = RichMarker.prototype.setPosition, RichMarker.prototype.position_changed = function() {
    this.draw()
  }, RichMarker.prototype.position_changed = RichMarker.prototype.position_changed, RichMarker.prototype.getAnchor = function() {
    return this.get("anchor")
  }, RichMarker.prototype.getAnchor = RichMarker.prototype.getAnchor, RichMarker.prototype.setAnchor = function(anchor) {
    this.set("anchor", anchor)
  }, RichMarker.prototype.setAnchor = RichMarker.prototype.setAnchor, RichMarker.prototype.anchor_changed = function() {
    this.draw()
  }, RichMarker.prototype.anchor_changed = RichMarker.prototype.anchor_changed, RichMarker.prototype.htmlToDocumentFragment_ = function(htmlString) {
    var tempDiv = document.createElement("DIV");
    if (tempDiv.innerHTML = htmlString, 1 == tempDiv.childNodes.length) return tempDiv.removeChild(tempDiv.firstChild);
    for (var fragment = document.createDocumentFragment(); tempDiv.firstChild;) fragment.appendChild(tempDiv.firstChild);
    return fragment
  }, RichMarker.prototype.removeChildren_ = function(node) {
    if (node)
      for (var child; child = node.firstChild;) node.removeChild(child)
  }, RichMarker.prototype.setContent = function(content) {
    this.set("content", content)
  }, RichMarker.prototype.setContent = RichMarker.prototype.setContent, RichMarker.prototype.getContent = function() {
    return this.get("content")
  }, RichMarker.prototype.getContent = RichMarker.prototype.getContent, RichMarker.prototype.content_changed = function() {
    if (this.markerContent_) {
      this.removeChildren_(this.markerContent_);
      var content = this.getContent();
      if (content) {
        "string" == typeof content && (content = content.replace(/^\s*([\S\s]*)\b\s*$/, "$1"), content = this.htmlToDocumentFragment_(content)), this.markerContent_.appendChild(content);
        for (var image, that = this, images = this.markerContent_.getElementsByTagName("IMG"), i = 0; image = images[i]; i++) google.maps.event.addDomListener(image, "mousedown", function(e) {
          that.getDraggable() && (e.preventDefault && e.preventDefault(), e.returnValue = !1)
        }), google.maps.event.addDomListener(image, "load", function() {
          that.draw()
        });
        google.maps.event.trigger(this, "domready")
      }
      this.ready_ && this.draw()
    }
  }, RichMarker.prototype.content_changed = RichMarker.prototype.content_changed, RichMarker.prototype.setCursor_ = function(whichCursor) {
    if (this.ready_) {
      var cursor = ""; - 1 !== navigator.userAgent.indexOf("Gecko/") ? ("dragging" == whichCursor && (cursor = "-moz-grabbing"), "dragready" == whichCursor && (cursor = "-moz-grab"), "draggable" == whichCursor && (cursor = "pointer")) : (("dragging" == whichCursor || "dragready" == whichCursor) && (cursor = "move"), "draggable" == whichCursor && (cursor = "pointer")), this.markerWrapper_.style.cursor != cursor && (this.markerWrapper_.style.cursor = cursor)
    }
  }, RichMarker.prototype.startDrag = function(e) {
    if (this.getDraggable() && !this.dragging_) {
      this.dragging_ = !0;
      var map = this.getMap();
      this.mapDraggable_ = map.get("draggable"), map.set("draggable", !1), this.mouseX_ = e.clientX, this.mouseY_ = e.clientY, this.setCursor_("dragready"), this.markerWrapper_.style.MozUserSelect = "none", this.markerWrapper_.style.KhtmlUserSelect = "none", this.markerWrapper_.style.WebkitUserSelect = "none", this.markerWrapper_.unselectable = "on", this.markerWrapper_.onselectstart = function() {
        return !1
      }, this.addDraggingListeners_(), google.maps.event.trigger(this, "dragstart")
    }
  }, RichMarker.prototype.stopDrag = function() {
    this.getDraggable() && this.dragging_ && (this.dragging_ = !1, this.getMap().set("draggable", this.mapDraggable_), this.mouseX_ = this.mouseY_ = this.mapDraggable_ = null, this.markerWrapper_.style.MozUserSelect = "", this.markerWrapper_.style.KhtmlUserSelect = "", this.markerWrapper_.style.WebkitUserSelect = "", this.markerWrapper_.unselectable = "off", this.markerWrapper_.onselectstart = function() {}, this.removeDraggingListeners_(), this.setCursor_("draggable"), google.maps.event.trigger(this, "dragend"), this.draw())
  }, RichMarker.prototype.drag = function(e) {
    if (!this.getDraggable() || !this.dragging_) return void this.stopDrag();
    var dx = this.mouseX_ - e.clientX,
    dy = this.mouseY_ - e.clientY;
    this.mouseX_ = e.clientX, this.mouseY_ = e.clientY;
    var left = parseInt(this.markerWrapper_.style.left, 10) - dx,
    top = parseInt(this.markerWrapper_.style.top, 10) - dy;
    this.markerWrapper_.style.left = left + "px", this.markerWrapper_.style.top = top + "px";
    var offset = this.getOffset_(),
    point = new google.maps.Point(left - offset.width, top - offset.height),
    projection = this.getProjection();
    this.setPosition(projection.fromDivPixelToLatLng(point)), this.setCursor_("dragging"), google.maps.event.trigger(this, "drag")
  }, RichMarker.prototype.removeDragListeners_ = function() {
    this.draggableListener_ && (google.maps.event.removeListener(this.draggableListener_), delete this.draggableListener_), this.setCursor_("")
  }, RichMarker.prototype.addDragging_ = function(node) {
    if (node) {
      var that = this;
      this.draggableListener_ = google.maps.event.addDomListener(node, "mousedown", function(e) {
        that.startDrag(e)
      }), this.setCursor_("draggable")
    }
  }, RichMarker.prototype.addDraggingListeners_ = function() {
    var that = this;
    this.markerWrapper_.setCapture ? (this.markerWrapper_.setCapture(!0), this.draggingListeners_ = [google.maps.event.addDomListener(this.markerWrapper_, "mousemove", function(e) {
      that.drag(e)
    }, !0), google.maps.event.addDomListener(this.markerWrapper_, "mouseup", function() {
      that.stopDrag(), that.markerWrapper_.releaseCapture()
    }, !0)]) : this.draggingListeners_ = [google.maps.event.addDomListener(window, "mousemove", function(e) {
      that.drag(e)
    }, !0), google.maps.event.addDomListener(window, "mouseup", function() {
      that.stopDrag()
    }, !0)]
  }, RichMarker.prototype.removeDraggingListeners_ = function() {
    if (this.draggingListeners_) {
      for (var listener, i = 0; listener = this.draggingListeners_[i]; i++) google.maps.event.removeListener(listener);
      this.draggingListeners_.length = 0
    }
  }, RichMarker.prototype.getOffset_ = function() {
    var anchor = this.getAnchor();
    if ("object" == typeof anchor) return anchor;
    var offset = new google.maps.Size(0, 0);
    if (!this.markerContent_) return offset;
    var width = this.markerContent_.offsetWidth,
    height = this.markerContent_.offsetHeight;
    switch (anchor) {
      case RichMarkerPosition.TOP_LEFT:
        break;
      case RichMarkerPosition.TOP:
        offset.width = -width / 2;
        break;
      case RichMarkerPosition.TOP_RIGHT:
        offset.width = -width;
        break;
      case RichMarkerPosition.LEFT:
        offset.height = -height / 2;
        break;
      case RichMarkerPosition.MIDDLE:
        offset.width = -width / 2, offset.height = -height / 2;
        break;
      case RichMarkerPosition.RIGHT:
        offset.width = -width, offset.height = -height / 2;
        break;
      case RichMarkerPosition.BOTTOM_LEFT:
        offset.height = -height;
        break;
      case RichMarkerPosition.BOTTOM:
        offset.width = -width / 2, offset.height = -height;
        break;
      case RichMarkerPosition.BOTTOM_RIGHT:
        offset.width = -width, offset.height = -height
    }
    return offset
  }, RichMarker.prototype.onAdd = function() {
    if (this.markerWrapper_ || (this.markerWrapper_ = document.createElement("DIV"), this.markerWrapper_.style.position = "absolute"), this.getZIndex() && (this.markerWrapper_.style.zIndex = this.getZIndex()), this.markerWrapper_.style.display = this.getVisible() ? "" : "none", !this.markerContent_) {
      this.markerContent_ = document.createElement("DIV"), this.markerWrapper_.appendChild(this.markerContent_);
      var that = this;
      google.maps.event.addDomListener(this.markerContent_, "click", function() {
        google.maps.event.trigger(that, "click")
      }), google.maps.event.addDomListener(this.markerContent_, "mouseover", function() {
        google.maps.event.trigger(that, "mouseover")
      }), google.maps.event.addDomListener(this.markerContent_, "mouseout", function() {
        google.maps.event.trigger(that, "mouseout")
      })
    }
    this.ready_ = !0, this.content_changed(), this.flat_changed(), this.draggable_changed();
    var panes = this.getPanes();
    panes && panes.overlayMouseTarget.appendChild(this.markerWrapper_), google.maps.event.trigger(this, "ready")
  }, RichMarker.prototype.onAdd = RichMarker.prototype.onAdd, RichMarker.prototype.draw = function() {
    if (this.ready_ && !this.dragging_) {
      var projection = this.getProjection();
      if (projection) {
        var latLng = this.get("position"),
        pos = projection.fromLatLngToDivPixel(latLng),
        offset = this.getOffset_();
        null != pos && (this.markerWrapper_.style.top = pos.y + offset.height + "px", this.markerWrapper_.style.left = pos.x + offset.width + "px");
        var height = this.markerContent_.offsetHeight,
        width = this.markerContent_.offsetWidth;
        width != this.get("width") && this.set("width", width), height != this.get("height") && this.set("height", height)
      }
    }
  }, RichMarker.prototype.draw = RichMarker.prototype.draw, RichMarker.prototype.onRemove = function() {
    this.markerWrapper_ && this.markerWrapper_.parentNode && this.markerWrapper_.parentNode.removeChild(this.markerWrapper_), this.removeDragListeners_()
  }, RichMarker.prototype.onRemove = RichMarker.prototype.onRemove;
  var RichMarkerPosition = {
    TOP_LEFT: 1,
    TOP: 2,
    TOP_RIGHT: 3,
    LEFT: 4,
    MIDDLE: 5,
    RIGHT: 6,
    BOTTOM_LEFT: 7,
    BOTTOM: 8,
    BOTTOM_RIGHT: 9
  };
  window.RichMarkerPosition = RichMarkerPosition
}

function FastClick(a) {
  "use strict";
    var b, c = this;
    if (this.trackingClick = !1, this.trackingClickStart = 0, this.targetElement = null, this.touchStartX = 0, this.touchStartY = 0, this.lastTouchIdentifier = 0, this.touchBoundary = 10, this.layer = a, !a || !a.nodeType) throw new TypeError("Layer must be a document node");
    this.onClick = function() {
      return FastClick.prototype.onClick.apply(c, arguments)
    }, this.onMouse = function() {
      return FastClick.prototype.onMouse.apply(c, arguments)
    }, this.onTouchStart = function() {
      return FastClick.prototype.onTouchStart.apply(c, arguments)
    }, this.onTouchMove = function() {
      return FastClick.prototype.onTouchMove.apply(c, arguments)
    }, this.onTouchEnd = function() {
      return FastClick.prototype.onTouchEnd.apply(c, arguments)
    }, this.onTouchCancel = function() {
      return FastClick.prototype.onTouchCancel.apply(c, arguments)
    }, FastClick.notNeeded(a) || (this.deviceIsAndroid && (a.addEventListener("mouseover", this.onMouse, !0), a.addEventListener("mousedown", this.onMouse, !0), a.addEventListener("mouseup", this.onMouse, !0)), a.addEventListener("click", this.onClick, !0), a.addEventListener("touchstart", this.onTouchStart, !1), a.addEventListener("touchmove", this.onTouchMove, !1), a.addEventListener("touchend", this.onTouchEnd, !1), a.addEventListener("touchcancel", this.onTouchCancel, !1), Event.prototype.stopImmediatePropagation || (a.removeEventListener = function(b, c, d) {
      var e = Node.prototype.removeEventListener;
      "click" === b ? e.call(a, b, c.hijacked || c, d) : e.call(a, b, c, d)
    }, a.addEventListener = function(b, c, d) {
      var e = Node.prototype.addEventListener;
      "click" === b ? e.call(a, b, c.hijacked || (c.hijacked = function(a) {
        a.propagationStopped || c(a)
      }), d) : e.call(a, b, c, d)
    }), "function" == typeof a.onclick && (b = a.onclick, a.addEventListener("click", function(a) {
      b(a)
    }, !1), a.onclick = null))
}

function increase_brightness(hex, percent) {
  var r = parseInt(hex.substr(1, 2), 16),
  g = parseInt(hex.substr(3, 2), 16),
  b = parseInt(hex.substr(5, 2), 16);
  return "" + (0 | 256 + r + (256 - r) * percent / 100).toString(16).substr(1) + (0 | 256 + g + (256 - g) * percent / 100).toString(16).substr(1) + (0 | 256 + b + (256 - b) * percent / 100).toString(16).substr(1)
}

function hideAddressBar(delay) {}

function OrientationChange() {
  updateAccordian()
}

function disableBodyScroll() {
  $(document).on("touchmove", function(e) {
    e.preventDefault()
  }), $("body").on("touchstart", ".scrollable", function(e) {
    0 === e.currentTarget.scrollTop ? e.currentTarget.scrollTop = 1 : e.currentTarget.scrollHeight === e.currentTarget.scrollTop + e.currentTarget.offsetHeight && (e.currentTarget.scrollTop -= 1)
  }), $("body").on("touchmove", ".scrollable", function(e) {
    $("body").hasClass("open") ? e.stopPropagation() : ($("#moreInfo").hasClass("active") || $("body").hasClass("choose")) && e.stopPropagation()
  })
}

function showDisclaimer() {
  mobileDevice && $("#disclaimer").delay(2e3).fadeIn().delay(1e4).fadeOut()
}

function updateState() {
  selectedLineId = parseInt(window.location.hash.slice(1)), updateRouteSelection(), shouldShowDisclaimer && (shouldShowDisclaimer = !1, showDisclaimer(), cookie.viewedDisclaimer = !0, applyCookie())
}

function updateRouteSelection() {
  selectedLineId > 0 ? ($("#accordian .selector").each(function(i, element) {
    $(element).attr("data-line-id") == selectedLineId ? $(element).addClass("selected") : $(element).removeClass("selected")
  }), closeFlyOut(!0), $("body").hasClass("choose") && ($("body").removeClass("choose"), setTimeout(function() {
    updateAccordian()
  }, 1e3)), null != setRouteTimeout && clearTimeout(setRouteTimeout), setTimeout(function() {
    setLine()
  }, 250)) : ($("#scheduleButton").hide(), $("#routeSelection a").each(function(i, element) {
    $(element).removeClass("selected")
  }), $('ul[id^="subRouteSelection"]').each(function(i, element) {
    $(element).removeClass("active")
  })), updateAccordian()
}

function toggleFlyOut() {
  flyOutOpen ? closeFlyOut() : openFlyOut()
}

function openFlyOut() {
  $("html").css("left", "0"), hideAddressBar(250), flyOutOpen = !0, $("body").removeClass("slow"), $("body").addClass("open"), $("body").hasClass("choose") && $("body").removeClass("choose")
}

function closeFlyOut(delay) {
  hideAddressBar(250), 1 == delay && $("body").addClass("slow"), flyOutOpen = !1, $("body").removeClass("open"), $("html").css("left", "0")
}

function toggleMoreInfo() {
  $("html").css("left", "0"), hideAddressBar(250), $("#moreInfo").hasClass("active") ? closeMoreInfo() : openMoreInfo()
}

function openMoreInfo() {
  $("#moreInfo").addClass("active")
}

function closeMoreInfo() {
  $("#moreInfo").removeClass("active"), $("#moreInfo .loadingIcon").removeClass("active")
}

function setMoreInfoContent(contentString, title) {
  $("#moreInfo .header .title").text(title), "http" == contentString.slice(0, 4) ? ($("#moreInfo .content").html(""), $("#moreInfo .loadingIcon").addClass("active"), "Line Schedule" == title && $.ajax({
    url: contentString + currentRouteID,
    type: "GET",
    dataType: "json",
    success: function(res) {
      $("#moreInfo .loadingIcon").removeClass("active"), $("#moreInfo .content").html(res.schedule)
    }
  })) : ($("#moreInfo .loadingIcon").removeClass("active"), $("#moreInfo .content").html(contentString))
}

function showHelp() {
  openMoreInfo(), setMoreInfoContent($("#helpContent").html(), "Help")
}

function giveFeedback() {
  openMoreInfo(), setMoreInfoContent($("#feedbackContent").html(), "Give Feedback")
}

function errorNotify() {
  openMoreInfo(), setMoreInfoContent($("#noticeContent").html(), "Notice")
}

function showSettings() {
  openMoreInfo(), setMoreInfoContent($("#settingsContent").html(), "Settings"), $("body").hasClass("showLabels") ? $('#moreInfo input[name="busLabelsToggle"]').prop("checked", !0) : $('#moreInfo input[name="busLabelsToggle"]').prop("checked", !1)
}

function showUpdate(index) {
  openMoreInfo(), -1 == $.inArray(index, cookie.viewedUpdates) && (cookie.viewedUpdates.push(index), applyCookie(), checkViewedUpdates()), setMoreInfoContent(updatesContent[index], "Updates")
}

function showAll() {
  null == bounds ? (map.setZoom(14), map.setCenter(new google.maps.LatLng(42.648686, -71.327847))) : map.fitBounds(bounds)
}

function applyCookie() {
  try {
    $.cookie(cookieName, cookie)
  } catch (error) {
    if (error.code !== DOMException.QUOTA_EXCEEDED_ERR || 0 !== storage.length) throw error
  }
}

function togglePositioning() {
  1 == trackingUser ? (trackingUser = !1, $("#locationButton").removeClass("active"), disablePositioning()) : (trackingUser = !0, $("#locationButton").addClass("active"), enablePositioning())
}

function enablePositioning() {
  lastZoom = map.getZoom(), initLocator()
}

function disablePositioning() {
  locationMarker.setMap(null), map.setZoom(lastZoom), navigator.geolocation.clearWatch(positionTimer)
}

function applyDataSource() {
  for (var i = busDataSource.length - 1; i >= 0; i--) {
    var line = busDataSource[i],
    $menuItem = $('<div class="section colored" data-line-id="' + line.Id + '" onclick="window.location.hash = \'' + line.Id + '\'"><div class="colorBlock" style="background-color:#' + line.Color + '"></div>' + line.Name + " " + line.Qualifier + "</div>");
    $menuItem.insertAfter($("#chooseHeading")), $menuItem.addClass("selector")
  }
  updateAccordian()
}

function updateAccordian() {
  var lastHeight = 0,
  zIndexes = $("#accordian>div").length;
  $("#accordian>div").each(function(i, e) {
    var $e = $(e);
    $e.css("height", $e.outerHeight() + "px"), $e.prev().hasClass("section") && $e.hasClass("subSection") ? $e.prev().hasClass("selected") ? (1 == mobileDevice ? $e.attr("style", "z-index:" + (zIndexes - i) + "; -webkit-transform:translate3D(0px," + lastHeight + "px,0px);") : $e.attr("style", "z-index:" + (zIndexes - i) + "; top:" + lastHeight + "px;"), lastHeight += $e.outerHeight()) : 1 == mobileDevice ? $e.attr("style", "z-index:" + (zIndexes - i) + "; -webkit-transform:translate3D(0px," + (lastHeight - $e.outerHeight()) + "px,0px);") : $e.attr("style", "z-index:" + (zIndexes - i) + "; top:" + (lastHeight - $e.outerHeight()) + "px;") : (1 == mobileDevice ? $e.attr("style", "z-index:" + (zIndexes - i) + "; -webkit-transform:translate3D(0px," + lastHeight + "px,0px);") : $e.attr("style", "z-index:" + (zIndexes - i) + "; top:" + lastHeight + "px;"), lastHeight += $e.outerHeight()), $("#accordian").css("height", lastHeight + "px")
  })
}

function getMessages() {
  var newHeight = 0;
  $.ajax({
    url: appDomain + "/api/Transportation/RoadsterRoutes/Messages/?apiKey=" + apiKey,
    type: "GET",
    dataType: "json",
    success: function(updates) {
      updates = updates.data, $("#updates").html(""), updatesContent = new Object;
      for (var i = 0; i < Math.min(updates.length, 3); i++) {
        var $menuItem = $('<div class="button small" updateId="' + updates[i].Id + '" onclick="showUpdate(\'' + updates[i].Id + "')\">" + updates[i].Content.substring(0, 30) + "...</div>");
        $menuItem.insertBefore("#updatesPlaceholder"), newHeight += $menuItem.height(), updateAccordian(), updatesContent[updates[i].Id] = "<h3>UMass Lowell Transportation Services</h3><p><em>" + fuzzyFacebookTime(updates[i].Timestamp) + "</em></p><p>" + updates[i].Content + '</p><p><a href="' + updates[i].FacebookUrl + '" target="_blank">View on Facebook</a></p>'
      }
      $("#updates").slideDown(250), checkViewedUpdates()
    },
    error: function() {
      $("#updatesTitle").hide(), $("#updates").hide()
    }
  })
}

function checkViewedUpdates() {
  $("#accordian .button[updateId]").each(function() {
    -1 == $.inArray($(this).attr("updateId"), cookie.viewedUpdates) ? $(this).addClass("new") : $(this).removeClass("new")
  })
}

function setLine() {
  clearBusStops(), clearBuses(), applyPath(), enableMap()
}

function applyPath() {
  var lineData = _.where(busDataSource, {
    Id: selectedLineId
  })[0];
  selectedLine = lineData, bounds = new google.maps.LatLngBounds;
  for (var path = [], r = 0; r < lineData.Paths[0].Polyline.length; r++) {
    var coord = new google.maps.LatLng(lineData.Paths[0].Polyline[r].Latitude, lineData.Paths[0].Polyline[r].Longitude);
    path.push(coord), bounds.extend(coord)
  }
  polyline.setPath(path), polyline.setOptions({
    strokeColor: "#" + lineData.Color
  });
  for (var s = 0; s < lineData.Stops.length; s++) addBusStop(lineData.Stops[s].Location.Latitude, lineData.Stops[s].Location.Longitude);
  trackBuses(), setTimeout("showAll()", 250)
}

function addBusStop(lat, lng) {
  var marker = new google.maps.Marker({
    position: new google.maps.LatLng(lat, lng),
                                      map: map,
                                      draggable: !1,
                                      icon: new google.maps.MarkerImage("images/busstop-marker.svg", null, null, new google.maps.Point(16, 16), null, new google.maps.Point(32, 32))
  });
  busStops.push(marker)
}

function clearBusStops() {
  for (var i = 0; i < busStops.length; i++) null != busStops[i] && (busStops[i].setMap(null), busStops[i] = null);
  busStops = []
}

function addBus(bus) {
  var $marker = $('<div class="directionIconContainer"><img id="marker_' + bus.Id + '" title="' + bus.Number + '" class="directionIcon" src="images/marker-direction.svg"/><img style="left:0px; top:1px; position:absolute;" src="' + appDomain + "/api/Transportation/RoadsterRoutes/BusIcon/?apiKey=" + apiKey + "&color=" + increase_brightness("#" + selectedLine.Color, 40) + '"/><div class="label">' + bus.Number + "</div></div>"),
  angle = bus.Heading,
  $markerIcon = $marker.find("img.directionIcon");
  $markerIcon.css("-webkit-transform", "rotate(" + angle + "deg)"), $markerIcon.css("-moz-transform", "rotate(" + angle + "deg)"), $markerIcon.css("-ms-transform", "rotate(" + angle + "deg)"), $markerIcon.css("transform", "rotate(" + angle + "deg)");
  var marker = new RichMarker({
    map: map,
    draggable: !1,
    optimized: !1,
    flat: !0,
    anchor: new google.maps.Size(-19, -19, "px", "px"),
                              content: $marker.html(),
                              busNumber: bus.Number,
                              busId: bus.Id
  });
  busMarkers[bus.Number] = marker, currentBuses.push(bus.Number), busPositionBuffers[bus.Number] = []
}

function clearBuses() {
  null != busUpdateTimeout && clearTimeout(busUpdateTimeout), _.each(busMarkers, function(m) {
    m.setMap(null), $(busAnimations[m.busNumber]).stop(!0), delete busMarkers[m], delete busAnimations[m.busNumber]
  }), busPositionBuffers = {}, currentBuses = [], busMarkers = {}, busAnimations = {}
}

function trackBuses() {
  $.ajax({
    url: appDomain + "/api/Transportation/RoadsterRoutes/BusesOnLine/?apiKey=" + apiKey + "&lineId=" + selectedLine.Id,
    type: "GET",
    dataType: "json",
    cache: !1,
    success: function(res) {
      var busesUpdated = [];
      _.each(res.data, function(bus) {
        _.contains(currentBuses, bus.Number) ? updateBusPosition(bus) : (addBus(bus), updateBusPosition(bus)), busesUpdated.push(bus.Number)
      });
      var busesToRemove = _.difference(currentBuses, busesUpdated);
      _.each(busesToRemove, function(b) {
        busMarkers[b].setMap(null), $(busAnimations[b]).stop(!0), delete busAnimations[b]
      }), currentBuses = busesUpdated
    }
  }).always(function() {
    busUpdateTimeout = setTimeout(function() {
      trackBuses()
    }, 5e3)
  })
}

function updateBusPosition(bus) {
  var coord = {
    lat: bus.Location.Latitude,
    lng: bus.Location.Longitude
  };
  moveMarker(bus.Number, bus.Location.Latitude, bus.Location.Longitude, bus.Heading), busPositionBuffers[bus.Number].push(coord)
}

function moveMarker(busNumber, lat, lng, angle) {
  var marker = busMarkers[busNumber]; - 1 == angle && (angle = 0), -1 == busLastAngles[busNumber] && (busLastAngles[busNumber] = 0), busLastAngles[busNumber] = angle;
  var $marker = $("#marker_" + marker.busId);
  null == busAnimations[busNumber] || void 0 == busAnimations[busNumber] ? (busAnimations[busNumber] = new Object, busAnimations[busNumber] = {
    x: lat,
    y: lng,
    rotation: angle
  }, marker.setPosition(new google.maps.LatLng(lat, lng))) : ($marker.hasClass("animated") || $marker.addClass("animated"), $marker.css("-webkit-transform", "rotate(" + angle + "deg)"), $marker.css("-moz-transform", "rotate(" + angle + "deg)"), $marker.css("-ms-transform", "rotate(" + angle + "deg)"), $marker.css("transform", "rotate(" + angle + "deg)"), busAnimations[busNumber].x = marker.getPosition().lat(), busAnimations[busNumber].y = marker.getPosition().lng(), busAnimations[busNumber].rotation = parseInt($marker.attr("rotation")), $(busAnimations[busNumber]).stop(!0).animate({
    x: lat,
    y: lng
  }, {
    duration: 1e3,
    step: function() {
      marker.setPosition(new google.maps.LatLng(busAnimations[busNumber].x, busAnimations[busNumber].y))
    }
  }))
}

function disableMap() {
  $("#overlay").addClass("active"), $("#screen .loadingIcon").addClass("active")
}

function enableMap() {
  $("#overlay").removeClass("active"), $("#screen .loadingIcon").removeClass("active")
}

function loadInitialData() {
  setTimeout(function() {
    $.ajax({
      url: appDomain + "/api/Transportation/RoadsterRoutes/Lines/?apiKey=" + apiKey,
      type: "GET",
      dataType: "json",
      success: function(res) {
        busDataSource = res.data, $("body").addClass("init"), applyDataSource(), getMessages(), setTimeout(initialLoadComplete, 1e3)
      },
      error: function() {
        $("#routeSelection .loadingIcon").addClass("error")
      }
    })
  }, 500)
}

function initialLoadComplete() {
  "" == location.hash || mobileDevice && ($("body").addClass("slow"), $("#screen").show()), initializeMap(), $(window).hashchange(function() {
    updateState()
  }), $(window).hashchange()
}

function busLabelsToggle() {
  $('#moreInfo input[name="busLabelsToggle"]').is(":checked") ? $("body").addClass("showLabels") : $("body").removeClass("showLabels")
}

function initializeMap() {
  myLatLng = new google.maps.LatLng(42.648686, -71.327847), myOptions = {
    zoom: 14,
    center: myLatLng,
    mapTypeId: google.maps.MapTypeId.ROADMAP,
    disableDefaultUI: !0,
    styles: styles
  }, map = new google.maps.Map(document.getElementById("mapCanvas"), myOptions);
  var rendererOptions = {
    map: map
  };
  directionsDisplay = new google.maps.DirectionsRenderer(rendererOptions), polyline.setMap(map), $("#mapCanvas").addClass("init"), setTimeout(function() {}, 250)
}

function updateMarker(marker, latitude, longitude, label, panTo) {
  marker.setPosition(new google.maps.LatLng(latitude, longitude)), null != label && marker.setTitle(label), null != panTo && (map.panTo(new google.maps.LatLng(latitude, longitude)), map.setZoom(panTo))
}

function initLocator() {
  locationMarker = new google.maps.Marker({
    map: map,
    icon: new google.maps.MarkerImage("images/location-marker.svg", null, null, new google.maps.Point(16, 16), null, new google.maps.Point(32, 32)),
                                          optimized: !1
  }), navigator.geolocation.getCurrentPosition(function() {}, function() {
    navigator.geolocation.clearWatch(positionTimer), $("#locationButton").hide()
  }, {
    timeout: 5e3,
    maximumAge: 6e5,
    enableHighAccuracy: !0
  }), positionTimer = navigator.geolocation.watchPosition(function(position) {
    0 == locatorHasInit ? (locatorHasInit = !0, updateMarker(locationMarker, position.coords.latitude, position.coords.longitude, null, 16)) : updateMarker(locationMarker, position.coords.latitude, position.coords.longitude)
  }), setTimeout(function() {
    navigator.geolocation.clearWatch(positionTimer)
  }, 3e5)
}

function sendFeedback() {
  $("#moreInfo .loadingIcon").addClass("active"), $("#moreInfo .content").fadeOut(250, function() {
    $.ajax({
      type: "POST",
      url: appDomain + "/cgi-bin/form-ajax.aspx",
      data: "mode=2&MailSubject=RoadsterRoutes%20Feedback&ThankYouMsg=submitted&ThankYouUrl=http://www.uml.edu&MailTo=websupport@uml.edu&SPAMSTOP=true&useragent=" + navigator.userAgent + "&rating=" + $("#moreInfo .content .range").val() + "&comments=" + $("#moreInfo .content .comments").val() + "&email=" + $("#moreInfo .content .email").val(),
           success: function() {
             $("#moreInfo .loadingIcon").removeClass("active"), $("#moreInfo .content").html("<p>Thank you, your feedback has been submitted.</p>"), $("#moreInfo .content").fadeIn(250)
           },
           error: function() {
             $("#moreInfo .loadingIcon").removeClass("active"), $("#moreInfo .content").html("<p>There was a problem submitting your feedback.</p>"), $("#moreInfo .content").fadeIn(250)
           }
    })
  })
}

function zoomIn() {
  map.setZoom(map.getZoom() + 1)
}

function zoomOut() {
  map.setZoom(map.getZoom() - 1)
}! function(a, b) {
  function G(a) {
    var b = F[a] = {};
    return p.each(a.split(s), function(a, c) {
      b[c] = !0
    }), b
  }

  function J(a, c, d) {
    if (d === b && 1 === a.nodeType) {
      var e = "data-" + c.replace(I, "-$1").toLowerCase();
      if (d = a.getAttribute(e), "string" == typeof d) {
        try {
          d = "true" === d ? !0 : "false" === d ? !1 : "null" === d ? null : +d + "" === d ? +d : H.test(d) ? p.parseJSON(d) : d
        } catch (f) {}
        p.data(a, c, d)
      } else d = b
    }
    return d
  }

  function K(a) {
    var b;
    for (b in a)
      if (("data" !== b || !p.isEmptyObject(a[b])) && "toJSON" !== b) return !1;
      return !0
  }

  function ba() {
    return !1
  }

  function bb() {
    return !0
  }

  function bh(a) {
    return !a || !a.parentNode || 11 === a.parentNode.nodeType
  }

  function bi(a, b) {
    do a = a[b]; while (a && 1 !== a.nodeType);
    return a
  }

  function bj(a, b, c) {
    if (b = b || 0, p.isFunction(b)) return p.grep(a, function(a, d) {
      var e = !!b.call(a, d, a);
      return e === c
    });
    if (b.nodeType) return p.grep(a, function(a) {
      return a === b === c
    });
    if ("string" == typeof b) {
      var d = p.grep(a, function(a) {
        return 1 === a.nodeType
      });
      if (be.test(b)) return p.filter(b, d, !c);
      b = p.filter(b, d)
    }
    return p.grep(a, function(a) {
      return p.inArray(a, b) >= 0 === c
    })
  }

  function bk(a) {
    var b = bl.split("|"),
    c = a.createDocumentFragment();
    if (c.createElement)
      for (; b.length;) c.createElement(b.pop());
      return c
  }

  function bC(a, b) {
    return a.getElementsByTagName(b)[0] || a.appendChild(a.ownerDocument.createElement(b))
  }

  function bD(a, b) {
    if (1 === b.nodeType && p.hasData(a)) {
      var c, d, e, f = p._data(a),
      g = p._data(b, f),
      h = f.events;
      if (h) {
        delete g.handle, g.events = {};
        for (c in h)
          for (d = 0, e = h[c].length; e > d; d++) p.event.add(b, c, h[c][d])
      }
      g.data && (g.data = p.extend({}, g.data))
    }
  }

  function bE(a, b) {
    var c;
    1 === b.nodeType && (b.clearAttributes && b.clearAttributes(), b.mergeAttributes && b.mergeAttributes(a), c = b.nodeName.toLowerCase(), "object" === c ? (b.parentNode && (b.outerHTML = a.outerHTML), p.support.html5Clone && a.innerHTML && !p.trim(b.innerHTML) && (b.innerHTML = a.innerHTML)) : "input" === c && bv.test(a.type) ? (b.defaultChecked = b.checked = a.checked, b.value !== a.value && (b.value = a.value)) : "option" === c ? b.selected = a.defaultSelected : "input" === c || "textarea" === c ? b.defaultValue = a.defaultValue : "script" === c && b.text !== a.text && (b.text = a.text), b.removeAttribute(p.expando))
  }

  function bF(a) {
    return "undefined" != typeof a.getElementsByTagName ? a.getElementsByTagName("*") : "undefined" != typeof a.querySelectorAll ? a.querySelectorAll("*") : []
  }

  function bG(a) {
    bv.test(a.type) && (a.defaultChecked = a.checked)
  }

  function bY(a, b) {
    if (b in a) return b;
    for (var c = b.charAt(0).toUpperCase() + b.slice(1), d = b, e = bW.length; e--;)
      if (b = bW[e] + c, b in a) return b;
      return d
  }

  function bZ(a, b) {
    return a = b || a, "none" === p.css(a, "display") || !p.contains(a.ownerDocument, a)
  }

  function b$(a, b) {
    for (var c, d, e = [], f = 0, g = a.length; g > f; f++) c = a[f], c.style && (e[f] = p._data(c, "olddisplay"), b ? (!e[f] && "none" === c.style.display && (c.style.display = ""), "" === c.style.display && bZ(c) && (e[f] = p._data(c, "olddisplay", cc(c.nodeName)))) : (d = bH(c, "display"), !e[f] && "none" !== d && p._data(c, "olddisplay", d)));
    for (f = 0; g > f; f++) c = a[f], c.style && (b && "none" !== c.style.display && "" !== c.style.display || (c.style.display = b ? e[f] || "" : "none"));
    return a
  }

  function b_(a, b, c) {
    var d = bP.exec(b);
    return d ? Math.max(0, d[1] - (c || 0)) + (d[2] || "px") : b
  }

  function ca(a, b, c, d) {
    for (var e = c === (d ? "border" : "content") ? 4 : "width" === b ? 1 : 0, f = 0; 4 > e; e += 2) "margin" === c && (f += p.css(a, c + bV[e], !0)), d ? ("content" === c && (f -= parseFloat(bH(a, "padding" + bV[e])) || 0), "margin" !== c && (f -= parseFloat(bH(a, "border" + bV[e] + "Width")) || 0)) : (f += parseFloat(bH(a, "padding" + bV[e])) || 0, "padding" !== c && (f += parseFloat(bH(a, "border" + bV[e] + "Width")) || 0));
    return f
  }

  function cb(a, b, c) {
    var d = "width" === b ? a.offsetWidth : a.offsetHeight,
    e = !0,
    f = p.support.boxSizing && "border-box" === p.css(a, "boxSizing");
    if (0 >= d || null == d) {
      if (d = bH(a, b), (0 > d || null == d) && (d = a.style[b]), bQ.test(d)) return d;
      e = f && (p.support.boxSizingReliable || d === a.style[b]), d = parseFloat(d) || 0
    }
    return d + ca(a, b, c || (f ? "border" : "content"), e) + "px"
  }

  function cc(a) {
    if (bS[a]) return bS[a];
    var b = p("<" + a + ">").appendTo(e.body),
    c = b.css("display");
    return b.remove(), ("none" === c || "" === c) && (bI = e.body.appendChild(bI || p.extend(e.createElement("iframe"), {
      frameBorder: 0,
      width: 0,
      height: 0
    })), bJ && bI.createElement || (bJ = (bI.contentWindow || bI.contentDocument).document, bJ.write("<!doctype html><html><body>"), bJ.close()), b = bJ.body.appendChild(bJ.createElement(a)), c = bH(b, "display"), e.body.removeChild(bI)), bS[a] = c, c
  }

  function ci(a, b, c, d) {
    var e;
    if (p.isArray(b)) p.each(b, function(b, e) {
      c || ce.test(a) ? d(a, e) : ci(a + "[" + ("object" == typeof e ? b : "") + "]", e, c, d)
    });
    else if (c || "object" !== p.type(b)) d(a, b);
    else
      for (e in b) ci(a + "[" + e + "]", b[e], c, d)
  }

  function cz(a) {
    return function(b, c) {
      "string" != typeof b && (c = b, b = "*");
      var d, e, f, g = b.toLowerCase().split(s),
      h = 0,
      i = g.length;
      if (p.isFunction(c))
        for (; i > h; h++) d = g[h], f = /^\+/.test(d), f && (d = d.substr(1) || "*"), e = a[d] = a[d] || [], e[f ? "unshift" : "push"](c)
    }
  }

  function cA(a, c, d, e, f, g) {
    f = f || c.dataTypes[0], g = g || {}, g[f] = !0;
    for (var h, i = a[f], j = 0, k = i ? i.length : 0, l = a === cv; k > j && (l || !h); j++) h = i[j](c, d, e), "string" == typeof h && (!l || g[h] ? h = b : (c.dataTypes.unshift(h), h = cA(a, c, d, e, h, g)));
    return (l || !h) && !g["*"] && (h = cA(a, c, d, e, "*", g)), h
  }

  function cB(a, c) {
    var d, e, f = p.ajaxSettings.flatOptions || {};
    for (d in c) c[d] !== b && ((f[d] ? a : e || (e = {}))[d] = c[d]);
    e && p.extend(!0, a, e)
  }

  function cC(a, c, d) {
    var e, f, g, h, i = a.contents,
    j = a.dataTypes,
    k = a.responseFields;
    for (f in k) f in d && (c[k[f]] = d[f]);
    for (;
         "*" === j[0];) j.shift(), e === b && (e = a.mimeType || c.getResponseHeader("content-type"));
    if (e)
      for (f in i)
        if (i[f] && i[f].test(e)) {
          j.unshift(f);
          break
        }
        if (j[0] in d) g = j[0];
        else {
          for (f in d) {
            if (!j[0] || a.converters[f + " " + j[0]]) {
              g = f;
              break
            }
            h || (h = f)
          }
          g = g || h
        }
        return g ? (g !== j[0] && j.unshift(g), d[g]) : void 0
  }

  function cD(a, b) {
    var c, d, e, f, g = a.dataTypes.slice(),
    h = g[0],
    i = {},
    j = 0;
    if (a.dataFilter && (b = a.dataFilter(b, a.dataType)), g[1])
      for (c in a.converters) i[c.toLowerCase()] = a.converters[c];
      for (; e = g[++j];)
        if ("*" !== e) {
          if ("*" !== h && h !== e) {
            if (c = i[h + " " + e] || i["* " + e], !c)
              for (d in i)
                if (f = d.split(" "), f[1] === e && (c = i[h + " " + f[0]] || i["* " + f[0]])) {
                  c === !0 ? c = i[d] : i[d] !== !0 && (e = f[0], g.splice(j--, 0, e));
                  break
                }
                if (c !== !0)
                  if (c && a["throws"]) b = c(b);
                  else try {
                    b = c(b)
                  } catch (k) {
                    return {
                      state: "parsererror",
                      error: c ? k : "No conversion from " + h + " to " + e
                    }
                  }
          }
          h = e
        }
        return {
          state: "success",
          data: b
        }
  }

  function cL() {
    try {
      return new a.XMLHttpRequest
    } catch (b) {}
  }

  function cM() {
    try {
      return new a.ActiveXObject("Microsoft.XMLHTTP")
    } catch (b) {}
  }

  function cU() {
    return setTimeout(function() {
      cN = b
    }, 0), cN = p.now()
  }

  function cV(a, b) {
    p.each(b, function(b, c) {
      for (var d = (cT[b] || []).concat(cT["*"]), e = 0, f = d.length; f > e; e++)
        if (d[e].call(a, b, c)) return
    })
  }

  function cW(a, b, c) {
    var d, e = 0,
    g = cS.length,
    h = p.Deferred().always(function() {
      delete i.elem
    }),
    i = function() {
      for (var b = cN || cU(), c = Math.max(0, j.startTime + j.duration - b), d = 1 - (c / j.duration || 0), e = 0, f = j.tweens.length; f > e; e++) j.tweens[e].run(d);
      return h.notifyWith(a, [j, d, c]), 1 > d && f ? c : (h.resolveWith(a, [j]), !1)
    },
    j = h.promise({
      elem: a,
      props: p.extend({}, b),
                  opts: p.extend(!0, {
                    specialEasing: {}
                  }, c),
                  originalProperties: b,
                  originalOptions: c,
                  startTime: cN || cU(),
                  duration: c.duration,
                  tweens: [],
                  createTween: function(b, c) {
                    var e = p.Tween(a, j.opts, b, c, j.opts.specialEasing[b] || j.opts.easing);
                    return j.tweens.push(e), e
                  },
                  stop: function(b) {
                    for (var c = 0, d = b ? j.tweens.length : 0; d > c; c++) j.tweens[c].run(1);
                  return b ? h.resolveWith(a, [j, b]) : h.rejectWith(a, [j, b]), this
                  }
    }),
    k = j.props;
    for (cX(k, j.opts.specialEasing); g > e; e++)
      if (d = cS[e].call(j, a, k, j.opts)) return d;
      return cV(j, k), p.isFunction(j.opts.start) && j.opts.start.call(a, j), p.fx.timer(p.extend(i, {
        anim: j,
        queue: j.opts.queue,
        elem: a
      })), j.progress(j.opts.progress).done(j.opts.done, j.opts.complete).fail(j.opts.fail).always(j.opts.always)
  }

  function cX(a, b) {
    var c, d, e, f, g;
    for (c in a)
      if (d = p.camelCase(c), e = b[d], f = a[c], p.isArray(f) && (e = f[1], f = a[c] = f[0]), c !== d && (a[d] = f, delete a[c]), g = p.cssHooks[d], g && "expand" in g) {
        f = g.expand(f), delete a[d];
        for (c in f) c in a || (a[c] = f[c], b[c] = e)
      } else b[d] = e
  }

  function cY(a, b, c) {
    var d, e, f, g, h, i, j, k, l = this,
    m = a.style,
    n = {},
    o = [],
    q = a.nodeType && bZ(a);
    c.queue || (j = p._queueHooks(a, "fx"), null == j.unqueued && (j.unqueued = 0, k = j.empty.fire, j.empty.fire = function() {
      j.unqueued || k()
    }), j.unqueued++, l.always(function() {
      l.always(function() {
        j.unqueued--, p.queue(a, "fx").length || j.empty.fire()
      })
    })), 1 === a.nodeType && ("height" in b || "width" in b) && (c.overflow = [m.overflow, m.overflowX, m.overflowY], "inline" === p.css(a, "display") && "none" === p.css(a, "float") && (p.support.inlineBlockNeedsLayout && "inline" !== cc(a.nodeName) ? m.zoom = 1 : m.display = "inline-block")), c.overflow && (m.overflow = "hidden", p.support.shrinkWrapBlocks || l.done(function() {
      m.overflow = c.overflow[0], m.overflowX = c.overflow[1], m.overflowY = c.overflow[2]
    }));
    for (d in b)
      if (f = b[d], cP.exec(f)) {
        if (delete b[d], f === (q ? "hide" : "show")) continue;
        o.push(d)
      }
      if (g = o.length)
        for (h = p._data(a, "fxshow") || p._data(a, "fxshow", {}), q ? p(a).show() : l.done(function() {
          p(a).hide()
        }), l.done(function() {
          var b;
          p.removeData(a, "fxshow", !0);
          for (b in n) p.style(a, b, n[b])
        }), d = 0; g > d; d++) e = o[d], i = l.createTween(e, q ? h[e] : 0), n[e] = h[e] || p.style(a, e), e in h || (h[e] = i.start, q && (i.end = i.start, i.start = "width" === e || "height" === e ? 1 : 0))
  }

  function cZ(a, b, c, d, e) {
    return new cZ.prototype.init(a, b, c, d, e)
  }

  function c$(a, b) {
    var c, d = {
      height: a
    },
    e = 0;
    for (b = b ? 1 : 0; 4 > e; e += 2 - b) c = bV[e], d["margin" + c] = d["padding" + c] = a;
    return b && (d.opacity = d.width = a), d
  }

  function da(a) {
    return p.isWindow(a) ? a : 9 === a.nodeType ? a.defaultView || a.parentWindow : !1
  }
  var c, d, e = a.document,
  f = a.location,
  g = a.navigator,
  h = a.jQuery,
  i = a.$,
  j = Array.prototype.push,
  k = Array.prototype.slice,
  l = Array.prototype.indexOf,
  m = Object.prototype.toString,
  n = Object.prototype.hasOwnProperty,
  o = String.prototype.trim,
  p = function(a, b) {
    return new p.fn.init(a, b, c)
  },
  q = /[\-+]?(?:\d*\.|)\d+(?:[eE][\-+]?\d+|)/.source,
  r = /\S/,
  s = /\s+/,
  t = /^[\s\uFEFF\xA0]+|[\s\uFEFF\xA0]+$/g,
  u = /^(?:[^#<]*(<[\w\W]+>)[^>]*$|#([\w\-]*)$)/,
  v = /^<(\w+)\s*\/?>(?:<\/\1>|)$/,
  w = /^[\],:{}\s]*$/,
  x = /(?:^|:|,)(?:\s*\[)+/g,
  y = /\\(?:["\\\/bfnrt]|u[\da-fA-F]{4})/g,
  z = /"[^"\\\r\n]*"|true|false|null|-?(?:\d\d*\.|)\d+(?:[eE][\-+]?\d+|)/g,
  A = /^-ms-/,
  B = /-([\da-z])/gi,
  C = function(a, b) {
    return (b + "").toUpperCase()
  },
  D = function() {
    e.addEventListener ? (e.removeEventListener("DOMContentLoaded", D, !1), p.ready()) : "complete" === e.readyState && (e.detachEvent("onreadystatechange", D), p.ready())
  },
  E = {};
  p.fn = p.prototype = {
    constructor: p,
    init: function(a, c, d) {
      var f, g, i;
      if (!a) return this;
      if (a.nodeType) return this.context = this[0] = a, this.length = 1, this;
      if ("string" == typeof a) {
        if (f = "<" === a.charAt(0) && ">" === a.charAt(a.length - 1) && a.length >= 3 ? [null, a, null] : u.exec(a), f && (f[1] || !c)) {
          if (f[1]) return c = c instanceof p ? c[0] : c, i = c && c.nodeType ? c.ownerDocument || c : e, a = p.parseHTML(f[1], i, !0), v.test(f[1]) && p.isPlainObject(c) && this.attr.call(a, c, !0), p.merge(this, a);
          if (g = e.getElementById(f[2]), g && g.parentNode) {
            if (g.id !== f[2]) return d.find(a);
            this.length = 1, this[0] = g
          }
          return this.context = e, this.selector = a, this
        }
        return !c || c.jquery ? (c || d).find(a) : this.constructor(c).find(a)
      }
      return p.isFunction(a) ? d.ready(a) : (a.selector !== b && (this.selector = a.selector, this.context = a.context), p.makeArray(a, this))
    },
    selector: "",
    jquery: "1.8.2",
    length: 0,
    size: function() {
      return this.length
    },
    toArray: function() {
      return k.call(this)
    },
    get: function(a) {
      return null == a ? this.toArray() : 0 > a ? this[this.length + a] : this[a]
    },
    pushStack: function(a, b, c) {
      var d = p.merge(this.constructor(), a);
      return d.prevObject = this, d.context = this.context, "find" === b ? d.selector = this.selector + (this.selector ? " " : "") + c : b && (d.selector = this.selector + "." + b + "(" + c + ")"), d
    },
    each: function(a, b) {
      return p.each(this, a, b)
    },
    ready: function(a) {
      return p.ready.promise().done(a), this
    },
    eq: function(a) {
      return a = +a, -1 === a ? this.slice(a) : this.slice(a, a + 1)
    },
    first: function() {
      return this.eq(0)
    },
    last: function() {
      return this.eq(-1)
    },
    slice: function() {
      return this.pushStack(k.apply(this, arguments), "slice", k.call(arguments).join(","))
    },
    map: function(a) {
      return this.pushStack(p.map(this, function(b, c) {
        return a.call(b, c, b)
      }))
    },
    end: function() {
      return this.prevObject || this.constructor(null)
    },
    push: j,
    sort: [].sort,
    splice: [].splice
  }, p.fn.init.prototype = p.fn, p.extend = p.fn.extend = function() {
    var a, c, d, e, f, g, h = arguments[0] || {},
    i = 1,
    j = arguments.length,
    k = !1;
    for ("boolean" == typeof h && (k = h, h = arguments[1] || {}, i = 2), "object" != typeof h && !p.isFunction(h) && (h = {}), j === i && (h = this, --i); j > i; i++)
      if (null != (a = arguments[i]))
        for (c in a) d = h[c], e = a[c], h !== e && (k && e && (p.isPlainObject(e) || (f = p.isArray(e))) ? (f ? (f = !1, g = d && p.isArray(d) ? d : []) : g = d && p.isPlainObject(d) ? d : {}, h[c] = p.extend(k, g, e)) : e !== b && (h[c] = e));
        return h
  }, p.extend({
    noConflict: function(b) {
      return a.$ === p && (a.$ = i), b && a.jQuery === p && (a.jQuery = h), p
    },
    isReady: !1,
    readyWait: 1,
    holdReady: function(a) {
      a ? p.readyWait++ : p.ready(!0)
    },
    ready: function(a) {
      if (a === !0 ? !--p.readyWait : !p.isReady) {
        if (!e.body) return setTimeout(p.ready, 1);
              p.isReady = !0, a !== !0 && --p.readyWait > 0 || (d.resolveWith(e, [p]), p.fn.trigger && p(e).trigger("ready").off("ready"))
      }
    },
    isFunction: function(a) {
      return "function" === p.type(a)
    },
    isArray: Array.isArray || function(a) {
      return "array" === p.type(a)
    },
    isWindow: function(a) {
      return null != a && a == a.window
    },
    isNumeric: function(a) {
      return !isNaN(parseFloat(a)) && isFinite(a)
    },
    type: function(a) {
      return null == a ? String(a) : E[m.call(a)] || "object"
    },
    isPlainObject: function(a) {
      if (!a || "object" !== p.type(a) || a.nodeType || p.isWindow(a)) return !1;
              try {
                if (a.constructor && !n.call(a, "constructor") && !n.call(a.constructor.prototype, "isPrototypeOf")) return !1
              } catch (c) {
                return !1
              }
              var d;
      for (d in a);
              return d === b || n.call(a, d)
    },
    isEmptyObject: function(a) {
      var b;
      for (b in a) return !1;
              return !0
    },
    error: function(a) {
      throw new Error(a)
    },
    parseHTML: function(a, b, c) {
      var d;
      return a && "string" == typeof a ? ("boolean" == typeof b && (c = b, b = 0), b = b || e, (d = v.exec(a)) ? [b.createElement(d[1])] : (d = p.buildFragment([a], b, c ? null : []), p.merge([], (d.cacheable ? p.clone(d.fragment) : d.fragment).childNodes))) : null
    },
    parseJSON: function(b) {
      return b && "string" == typeof b ? (b = p.trim(b), a.JSON && a.JSON.parse ? a.JSON.parse(b) : w.test(b.replace(y, "@").replace(z, "]").replace(x, "")) ? new Function("return " + b)() : void p.error("Invalid JSON: " + b)) : null
    },
    parseXML: function(c) {
      var d, e;
      if (!c || "string" != typeof c) return null;
              try {
                a.DOMParser ? (e = new DOMParser, d = e.parseFromString(c, "text/xml")) : (d = new ActiveXObject("Microsoft.XMLDOM"), d.async = "false", d.loadXML(c))
              } catch (f) {
                d = b
              }
              return (!d || !d.documentElement || d.getElementsByTagName("parsererror").length) && p.error("Invalid XML: " + c), d
    },
    noop: function() {},
              globalEval: function(b) {
                b && r.test(b) && (a.execScript || function(b) {
                  a.eval.call(a, b)
                })(b)
              },
              camelCase: function(a) {
                return a.replace(A, "ms-").replace(B, C)
              },
              nodeName: function(a, b) {
                return a.nodeName && a.nodeName.toLowerCase() === b.toLowerCase()
              },
              each: function(a, c, d) {
                var e, f = 0,
              g = a.length,
              h = g === b || p.isFunction(a);
              if (d)
                if (h) {
                  for (e in a)
                    if (c.apply(a[e], d) === !1) break
                } else
                  for (; g > f && c.apply(a[f++], d) !== !1;);
              else if (h) {
                for (e in a)
                  if (c.call(a[e], e, a[e]) === !1) break
              } else
                for (; g > f && c.call(a[f], f, a[f++]) !== !1;);
              return a
              },
              trim: o && !o.call(" ") ? function(a) {
                return null == a ? "" : o.call(a)
              } : function(a) {
                return null == a ? "" : (a + "").replace(t, "")
              },
              makeArray: function(a, b) {
                var c, d = b || [];
                return null != a && (c = p.type(a), null == a.length || "string" === c || "function" === c || "regexp" === c || p.isWindow(a) ? j.call(d, a) : p.merge(d, a)), d
              },
              inArray: function(a, b, c) {
                var d;
                if (b) {
                  if (l) return l.call(b, a, c);
              for (d = b.length, c = c ? 0 > c ? Math.max(0, d + c) : c : 0; d > c; c++)
                if (c in b && b[c] === a) return c
                }
                return -1
              },
              merge: function(a, c) {
                var d = c.length,
              e = a.length,
              f = 0;
              if ("number" == typeof d)
                for (; d > f; f++) a[e++] = c[f];
              else
                for (; c[f] !== b;) a[e++] = c[f++];
              return a.length = e, a
              },
              grep: function(a, b, c) {
                var d, e = [],
              f = 0,
              g = a.length;
              for (c = !!c; g > f; f++) d = !!b(a[f], f), c !== d && e.push(a[f]);
              return e
              },
              map: function(a, c, d) {
                var e, f, g = [],
              h = 0,
              i = a.length,
              j = a instanceof p || i !== b && "number" == typeof i && (i > 0 && a[0] && a[i - 1] || 0 === i || p.isArray(a));
              if (j)
                for (; i > h; h++) e = c(a[h], h, d), null != e && (g[g.length] = e);
              else
                for (f in a) e = c(a[f], f, d), null != e && (g[g.length] = e);
              return g.concat.apply([], g)
              },
              guid: 1,
              proxy: function(a, c) {
                var d, e, f;
                return "string" == typeof c && (d = a[c], c = a, a = d), p.isFunction(a) ? (e = k.call(arguments, 2), f = function() {
                  return a.apply(c, e.concat(k.call(arguments)))
                }, f.guid = a.guid = a.guid || p.guid++, f) : b
              },
              access: function(a, c, d, e, f, g, h) {
                var i, j = null == d,
              k = 0,
              l = a.length;
              if (d && "object" == typeof d) {
                for (k in d) p.access(a, c, k, d[k], 1, g, e);
              f = 1
              } else if (e !== b) {
                if (i = h === b && p.isFunction(e), j && (i ? (i = c, c = function(a, b, c) {
                  return i.call(p(a), c)
                }) : (c.call(a, e), c = null)), c)
                  for (; l > k; k++) c(a[k], d, i ? e.call(a[k], k, c(a[k], d)) : e, h);
              f = 1
              }
              return f ? a : j ? c.call(a) : l ? c(a[0], d) : g
              },
              now: function() {
                return (new Date).getTime()
              }
  }), p.ready.promise = function(b) {
    if (!d)
      if (d = p.Deferred(), "complete" === e.readyState) setTimeout(p.ready, 1);
      else if (e.addEventListener) e.addEventListener("DOMContentLoaded", D, !1), a.addEventListener("load", p.ready, !1);
      else {
        e.attachEvent("onreadystatechange", D), a.attachEvent("onload", p.ready);
        var c = !1;
        try {
          c = null == a.frameElement && e.documentElement
        } catch (f) {}
        c && c.doScroll && function g() {
          if (!p.isReady) {
            try {
              c.doScroll("left")
            } catch (a) {
              return setTimeout(g, 50)
            }
            p.ready()
          }
        }()
      }
      return d.promise(b)
  }, p.each("Boolean Number String Function Array Date RegExp Object".split(" "), function(a, b) {
    E["[object " + b + "]"] = b.toLowerCase()
  }), c = p(e);
  var F = {};
  p.Callbacks = function(a) {
    a = "string" == typeof a ? F[a] || G(a) : p.extend({}, a);
    var c, d, e, f, g, h, i = [],
    j = !a.once && [],
    k = function(b) {
      for (c = a.memory && b, d = !0, h = f || 0, f = 0, g = i.length, e = !0; i && g > h; h++)
        if (i[h].apply(b[0], b[1]) === !1 && a.stopOnFalse) {
          c = !1;
          break
        }
        e = !1, i && (j ? j.length && k(j.shift()) : c ? i = [] : l.disable())
    },
    l = {
      add: function() {
        if (i) {
          var b = i.length;
          ! function d(b) {
            p.each(b, function(b, c) {
              var e = p.type(c);
              "function" !== e || a.unique && l.has(c) ? c && c.length && "string" !== e && d(c) : i.push(c)
            })
          }(arguments), e ? g = i.length : c && (f = b, k(c))
        }
        return this
      },
      remove: function() {
        return i && p.each(arguments, function(a, b) {
          for (var c;
               (c = p.inArray(b, i, c)) > -1;) i.splice(c, 1), e && (g >= c && g--, h >= c && h--)
        }), this
      },
      has: function(a) {
        return p.inArray(a, i) > -1
      },
      empty: function() {
        return i = [], this
      },
      disable: function() {
        return i = j = c = b, this
      },
      disabled: function() {
        return !i
      },
      lock: function() {
        return j = b, c || l.disable(), this
      },
      locked: function() {
        return !j
      },
      fireWith: function(a, b) {
        return b = b || [], b = [a, b.slice ? b.slice() : b], i && (!d || j) && (e ? j.push(b) : k(b)), this
      },
      fire: function() {
        return l.fireWith(this, arguments), this
      },
      fired: function() {
        return !!d
      }
    };
    return l
  }, p.extend({
    Deferred: function(a) {
      var b = [
      ["resolve", "done", p.Callbacks("once memory"), "resolved"],
              ["reject", "fail", p.Callbacks("once memory"), "rejected"],
              ["notify", "progress", p.Callbacks("memory")]
      ],
      c = "pending",
      d = {
        state: function() {
          return c
        },
        always: function() {
          return e.done(arguments).fail(arguments), this
        },
        then: function() {
          var a = arguments;
          return p.Deferred(function(c) {
            p.each(b, function(b, d) {
              var f = d[0],
              g = a[b];
              e[d[1]](p.isFunction(g) ? function() {
                var a = g.apply(this, arguments);
                a && p.isFunction(a.promise) ? a.promise().done(c.resolve).fail(c.reject).progress(c.notify) : c[f + "With"](this === e ? c : this, [a])
              } : c[f])
            }), a = null
          }).promise()
        },
        promise: function(a) {
          return null != a ? p.extend(a, d) : d
        }
      },
      e = {};
      return d.pipe = d.then, p.each(b, function(a, f) {
        var g = f[2],
        h = f[3];
        d[f[1]] = g.add, h && g.add(function() {
          c = h
        }, b[1 ^ a][2].disable, b[2][2].lock), e[f[0]] = g.fire, e[f[0] + "With"] = g.fireWith
      }), d.promise(e), a && a.call(e, e), e
    },
    when: function(a) {
      var h, i, j, b = 0,
      c = k.call(arguments),
              d = c.length,
              e = 1 !== d || a && p.isFunction(a.promise) ? d : 0,
              f = 1 === e ? a : p.Deferred(),
              g = function(a, b, c) {
                return function(d) {
                  b[a] = this, c[a] = arguments.length > 1 ? k.call(arguments) : d, c === h ? f.notifyWith(b, c) : --e || f.resolveWith(b, c)
                }
              };
              if (d > 1)
                for (h = new Array(d), i = new Array(d), j = new Array(d); d > b; b++) c[b] && p.isFunction(c[b].promise) ? c[b].promise().done(g(b, j, c)).fail(f.reject).progress(g(b, i, h)) : --e;
              return e || f.resolveWith(j, c), f.promise()
    }
  }), p.support = function() {
    var b, c, d, f, g, h, i, j, k, l, m, n = e.createElement("div");
    if (n.setAttribute("className", "t"), n.innerHTML = "  <link/><table></table><a href='/a'>a</a><input type='checkbox'/>", c = n.getElementsByTagName("*"), d = n.getElementsByTagName("a")[0], d.style.cssText = "top:1px;float:left;opacity:.5", !c || !c.length) return {};
    f = e.createElement("select"), g = f.appendChild(e.createElement("option")), h = n.getElementsByTagName("input")[0], b = {
      leadingWhitespace: 3 === n.firstChild.nodeType,
      tbody: !n.getElementsByTagName("tbody").length,
      htmlSerialize: !!n.getElementsByTagName("link").length,
      style: /top/.test(d.getAttribute("style")),
      hrefNormalized: "/a" === d.getAttribute("href"),
      opacity: /^0.5/.test(d.style.opacity),
      cssFloat: !!d.style.cssFloat,
      checkOn: "on" === h.value,
      optSelected: g.selected,
      getSetAttribute: "t" !== n.className,
      enctype: !!e.createElement("form").enctype,
      html5Clone: "<:nav></:nav>" !== e.createElement("nav").cloneNode(!0).outerHTML,
      boxModel: "CSS1Compat" === e.compatMode,
      submitBubbles: !0,
      changeBubbles: !0,
      focusinBubbles: !1,
      deleteExpando: !0,
      noCloneEvent: !0,
      inlineBlockNeedsLayout: !1,
      shrinkWrapBlocks: !1,
      reliableMarginRight: !0,
      boxSizingReliable: !0,
      pixelPosition: !1
    }, h.checked = !0, b.noCloneChecked = h.cloneNode(!0).checked, f.disabled = !0, b.optDisabled = !g.disabled;
    try {
      delete n.test
    } catch (o) {
      b.deleteExpando = !1
    }
    if (!n.addEventListener && n.attachEvent && n.fireEvent && (n.attachEvent("onclick", m = function() {
      b.noCloneEvent = !1
    }), n.cloneNode(!0).fireEvent("onclick"), n.detachEvent("onclick", m)), h = e.createElement("input"), h.value = "t", h.setAttribute("type", "radio"), b.radioValue = "t" === h.value, h.setAttribute("checked", "checked"), h.setAttribute("name", "t"), n.appendChild(h), i = e.createDocumentFragment(), i.appendChild(n.lastChild), b.checkClone = i.cloneNode(!0).cloneNode(!0).lastChild.checked, b.appendChecked = h.checked, i.removeChild(h), i.appendChild(n), n.attachEvent)
      for (k in {
        submit: !0,
        change: !0,
        focusin: !0
      }) j = "on" + k, l = j in n, l || (n.setAttribute(j, "return;"), l = "function" == typeof n[j]), b[k + "Bubbles"] = l;
      return p(function() {
        var c, d, f, g, h = "padding:0;margin:0;border:0;display:block;overflow:hidden;",
        i = e.getElementsByTagName("body")[0];
        i && (c = e.createElement("div"), c.style.cssText = "visibility:hidden;border:0;width:0;height:0;position:static;top:0;margin-top:1px", i.insertBefore(c, i.firstChild), d = e.createElement("div"), c.appendChild(d), d.innerHTML = "<table><tr><td></td><td>t</td></tr></table>", f = d.getElementsByTagName("td"), f[0].style.cssText = "padding:0;margin:0;border:0;display:none", l = 0 === f[0].offsetHeight, f[0].style.display = "", f[1].style.display = "none", b.reliableHiddenOffsets = l && 0 === f[0].offsetHeight, d.innerHTML = "", d.style.cssText = "box-sizing:border-box;-moz-box-sizing:border-box;-webkit-box-sizing:border-box;padding:1px;border:1px;display:block;width:4px;margin-top:1%;position:absolute;top:1%;", b.boxSizing = 4 === d.offsetWidth, b.doesNotIncludeMarginInBodyOffset = 1 !== i.offsetTop, a.getComputedStyle && (b.pixelPosition = "1%" !== (a.getComputedStyle(d, null) || {}).top, b.boxSizingReliable = "4px" === (a.getComputedStyle(d, null) || {
          width: "4px"
        }).width, g = e.createElement("div"), g.style.cssText = d.style.cssText = h, g.style.marginRight = g.style.width = "0", d.style.width = "1px", d.appendChild(g), b.reliableMarginRight = !parseFloat((a.getComputedStyle(g, null) || {}).marginRight)), "undefined" != typeof d.style.zoom && (d.innerHTML = "", d.style.cssText = h + "width:1px;padding:1px;display:inline;zoom:1", b.inlineBlockNeedsLayout = 3 === d.offsetWidth, d.style.display = "block", d.style.overflow = "visible", d.innerHTML = "<div></div>", d.firstChild.style.width = "5px", b.shrinkWrapBlocks = 3 !== d.offsetWidth, c.style.zoom = 1), i.removeChild(c), c = d = f = g = null)
      }), i.removeChild(n), c = d = f = g = h = i = n = null, b
  }();
  var H = /(?:\{[\s\S]*\}|\[[\s\S]*\])$/,
  I = /([A-Z])/g;
  p.extend({
    cache: {},
    deletedIds: [],
    uuid: 0,
    expando: "jQuery" + (p.fn.jquery + Math.random()).replace(/\D/g, ""),
           noData: {
             embed: !0,
           object: "clsid:D27CDB6E-AE6D-11cf-96B8-444553540000",
           applet: !0
           },
           hasData: function(a) {
             return a = a.nodeType ? p.cache[a[p.expando]] : a[p.expando], !!a && !K(a)
           },
           data: function(a, c, d, e) {
             if (p.acceptData(a)) {
               var f, g, h = p.expando,
           i = "string" == typeof c,
           j = a.nodeType,
           k = j ? p.cache : a,
           l = j ? a[h] : a[h] && h;
           if (l && k[l] && (e || k[l].data) || !i || d !== b) return l || (j ? a[h] = l = p.deletedIds.pop() || p.guid++ : l = h), k[l] || (k[l] = {}, j || (k[l].toJSON = p.noop)), ("object" == typeof c || "function" == typeof c) && (e ? k[l] = p.extend(k[l], c) : k[l].data = p.extend(k[l].data, c)), f = k[l], e || (f.data || (f.data = {}), f = f.data), d !== b && (f[p.camelCase(c)] = d), i ? (g = f[c], null == g && (g = f[p.camelCase(c)])) : g = f, g
             }
           },
           removeData: function(a, b, c) {
             if (p.acceptData(a)) {
               var d, e, f, g = a.nodeType,
           h = g ? p.cache : a,
           i = g ? a[p.expando] : p.expando;
           if (h[i]) {
             if (b && (d = c ? h[i] : h[i].data)) {
               p.isArray(b) || (b in d ? b = [b] : (b = p.camelCase(b), b = b in d ? [b] : b.split(" ")));
               for (e = 0, f = b.length; f > e; e++) delete d[b[e]];
           if (!(c ? K : p.isEmptyObject)(d)) return
             }(c || (delete h[i].data, K(h[i]))) && (g ? p.cleanData([a], !0) : p.support.deleteExpando || h != h.window ? delete h[i] : h[i] = null)
           }
             }
           },
           _data: function(a, b, c) {
             return p.data(a, b, c, !0)
           },
           acceptData: function(a) {
             var b = a.nodeName && p.noData[a.nodeName.toLowerCase()];
             return !b || b !== !0 && a.getAttribute("classid") === b
           }
  }), p.fn.extend({
    data: function(a, c) {
      var d, e, f, g, h, i = this[0],
      j = 0,
      k = null;
      if (a === b) {
        if (this.length && (k = p.data(i), 1 === i.nodeType && !p._data(i, "parsedAttrs"))) {
          for (f = i.attributes, h = f.length; h > j; j++) g = f[j].name, g.indexOf("data-") || (g = p.camelCase(g.substring(5)), J(i, g, k[g]));
                  p._data(i, "parsedAttrs", !0)
        }
        return k
      }
      return "object" == typeof a ? this.each(function() {
        p.data(this, a)
      }) : (d = a.split(".", 2), d[1] = d[1] ? "." + d[1] : "", e = d[1] + "!", p.access(this, function(c) {
        return c === b ? (k = this.triggerHandler("getData" + e, [d[0]]), k === b && i && (k = p.data(i, a), k = J(i, a, k)), k === b && d[1] ? this.data(d[0]) : k) : (d[1] = c, void this.each(function() {
          var b = p(this);
          b.triggerHandler("setData" + e, d), p.data(this, a, c), b.triggerHandler("changeData" + e, d)
        }))
      }, null, c, arguments.length > 1, null, !1))
    },
    removeData: function(a) {
      return this.each(function() {
        p.removeData(this, a)
      })
    }
  }), p.extend({
    queue: function(a, b, c) {
      var d;
      return a ? (b = (b || "fx") + "queue", d = p._data(a, b), c && (!d || p.isArray(c) ? d = p._data(a, b, p.makeArray(c)) : d.push(c)), d || []) : void 0
    },
    dequeue: function(a, b) {
      b = b || "fx";
      var c = p.queue(a, b),
               d = c.length,
               e = c.shift(),
               f = p._queueHooks(a, b),
               g = function() {
                 p.dequeue(a, b)
               };
               "inprogress" === e && (e = c.shift(), d--), e && ("fx" === b && c.unshift("inprogress"), delete f.stop, e.call(a, g, f)), !d && f && f.empty.fire()
    },
    _queueHooks: function(a, b) {
      var c = b + "queueHooks";
      return p._data(a, c) || p._data(a, c, {
        empty: p.Callbacks("once memory").add(function() {
          p.removeData(a, b + "queue", !0), p.removeData(a, c, !0)
        })
      })
    }
  }), p.fn.extend({
    queue: function(a, c) {
      var d = 2;
      return "string" != typeof a && (c = a, a = "fx", d--), arguments.length < d ? p.queue(this[0], a) : c === b ? this : this.each(function() {
        var b = p.queue(this, a, c);
        p._queueHooks(this, a), "fx" === a && "inprogress" !== b[0] && p.dequeue(this, a)
      })
    },
    dequeue: function(a) {
      return this.each(function() {
        p.dequeue(this, a)
      })
    },
    delay: function(a, b) {
      return a = p.fx ? p.fx.speeds[a] || a : a, b = b || "fx", this.queue(b, function(b, c) {
        var d = setTimeout(b, a);
        c.stop = function() {
          clearTimeout(d)
        }
      })
    },
    clearQueue: function(a) {
      return this.queue(a || "fx", [])
    },
    promise: function(a, c) {
      var d, e = 1,
      f = p.Deferred(),
                  g = this,
                  h = this.length,
                  i = function() {
                    --e || f.resolveWith(g, [g])
                  };
                  for ("string" != typeof a && (c = a, a = b), a = a || "fx"; h--;) d = p._data(g[h], a + "queueHooks"), d && d.empty && (e++, d.empty.add(i));
                  return i(), f.promise(c)
    }
  });
  var L, M, N, O = /[\t\r\n]/g,
  P = /\r/g,
  Q = /^(?:button|input)$/i,
  R = /^(?:button|input|object|select|textarea)$/i,
  S = /^a(?:rea|)$/i,
  T = /^(?:autofocus|autoplay|async|checked|controls|defer|disabled|hidden|loop|multiple|open|readonly|required|scoped|selected)$/i,
  U = p.support.getSetAttribute;
  p.fn.extend({
    attr: function(a, b) {
      return p.access(this, p.attr, a, b, arguments.length > 1)
    },
    removeAttr: function(a) {
      return this.each(function() {
        p.removeAttr(this, a)
      })
    },
    prop: function(a, b) {
      return p.access(this, p.prop, a, b, arguments.length > 1)
    },
    removeProp: function(a) {
      return a = p.propFix[a] || a, this.each(function() {
        try {
          this[a] = b, delete this[a]
        } catch (c) {}
      })
    },
    addClass: function(a) {
      var b, c, d, e, f, g, h;
      if (p.isFunction(a)) return this.each(function(b) {
        p(this).addClass(a.call(this, b, this.className))
      });
      if (a && "string" == typeof a)
        for (b = a.split(s), c = 0, d = this.length; d > c; c++)
          if (e = this[c], 1 === e.nodeType)
            if (e.className || 1 !== b.length) {
              for (f = " " + e.className + " ", g = 0, h = b.length; h > g; g++) f.indexOf(" " + b[g] + " ") < 0 && (f += b[g] + " ");
              e.className = p.trim(f)
            } else e.className = a;
              return this
    },
    removeClass: function(a) {
      var c, d, e, f, g, h, i;
      if (p.isFunction(a)) return this.each(function(b) {
        p(this).removeClass(a.call(this, b, this.className))
      });
      if (a && "string" == typeof a || a === b)
        for (c = (a || "").split(s), h = 0, i = this.length; i > h; h++)
          if (e = this[h], 1 === e.nodeType && e.className) {
            for (d = (" " + e.className + " ").replace(O, " "), f = 0, g = c.length; g > f; f++)
              for (; d.indexOf(" " + c[f] + " ") >= 0;) d = d.replace(" " + c[f] + " ", " ");
              e.className = a ? p.trim(d) : ""
          }
          return this
    },
    toggleClass: function(a, b) {
      var c = typeof a,
      d = "boolean" == typeof b;
      return this.each(p.isFunction(a) ? function(c) {
        p(this).toggleClass(a.call(this, c, this.className, b), b)
      } : function() {
        if ("string" === c)
          for (var e, f = 0, g = p(this), h = b, i = a.split(s); e = i[f++];) h = d ? h : !g.hasClass(e), g[h ? "addClass" : "removeClass"](e);
                       else("undefined" === c || "boolean" === c) && (this.className && p._data(this, "__className__", this.className), this.className = this.className || a === !1 ? "" : p._data(this, "__className__") || "")
      })
    },
    hasClass: function(a) {
      for (var b = " " + a + " ", c = 0, d = this.length; d > c; c++)
        if (1 === this[c].nodeType && (" " + this[c].className + " ").replace(O, " ").indexOf(b) >= 0) return !0;
              return !1
    },
    val: function(a) {
      var c, d, e, f = this[0]; {
        if (arguments.length) return e = p.isFunction(a), this.each(function(d) {
          var f, g = p(this);
          1 === this.nodeType && (f = e ? a.call(this, d, g.val()) : a, null == f ? f = "" : "number" == typeof f ? f += "" : p.isArray(f) && (f = p.map(f, function(a) {
            return null == a ? "" : a + ""
          })), c = p.valHooks[this.type] || p.valHooks[this.nodeName.toLowerCase()], c && "set" in c && c.set(this, f, "value") !== b || (this.value = f))
        });
        if (f) return c = p.valHooks[f.type] || p.valHooks[f.nodeName.toLowerCase()], c && "get" in c && (d = c.get(f, "value")) !== b ? d : (d = f.value, "string" == typeof d ? d.replace(P, "") : null == d ? "" : d)
      }
    }
  }), p.extend({
    valHooks: {
      option: {
        get: function(a) {
          var b = a.attributes.value;
          return !b || b.specified ? a.value : a.text
        }
      },
      select: {
        get: function(a) {
          var b, c, d, e, f = a.selectedIndex,
          g = [],
          h = a.options,
          i = "select-one" === a.type;
          if (0 > f) return null;
               for (c = i ? f : 0, d = i ? f + 1 : h.length; d > c; c++)
                 if (e = h[c], !(!e.selected || (p.support.optDisabled ? e.disabled : null !== e.getAttribute("disabled")) || e.parentNode.disabled && p.nodeName(e.parentNode, "optgroup"))) {
                   if (b = p(e).val(), i) return b;
               g.push(b)
                 }
                 return i && !g.length && h.length ? p(h[f]).val() : g
        },
        set: function(a, b) {
          var c = p.makeArray(b);
          return p(a).find("option").each(function() {
            this.selected = p.inArray(p(this).val(), c) >= 0
          }), c.length || (a.selectedIndex = -1), c
        }
      }
    },
    attrFn: {},
    attr: function(a, c, d, e) {
      var f, g, h, i = a.nodeType;
      if (a && 3 !== i && 8 !== i && 2 !== i) return e && p.isFunction(p.fn[c]) ? p(a)[c](d) : "undefined" == typeof a.getAttribute ? p.prop(a, c, d) : (h = 1 !== i || !p.isXMLDoc(a), h && (c = c.toLowerCase(), g = p.attrHooks[c] || (T.test(c) ? M : L)), d !== b ? null === d ? void p.removeAttr(a, c) : g && "set" in g && h && (f = g.set(a, d, c)) !== b ? f : (a.setAttribute(c, d + ""), d) : g && "get" in g && h && null !== (f = g.get(a, c)) ? f : (f = a.getAttribute(c), null === f ? b : f))
    },
    removeAttr: function(a, b) {
      var c, d, e, f, g = 0;
      if (b && 1 === a.nodeType)
        for (d = b.split(s); g < d.length; g++) e = d[g], e && (c = p.propFix[e] || e, f = T.test(e), f || p.attr(a, e, ""), a.removeAttribute(U ? e : c), f && c in a && (a[c] = !1))
    },
    attrHooks: {
      type: {
        set: function(a, b) {
          if (Q.test(a.nodeName) && a.parentNode) p.error("type property can't be changed");
               else if (!p.support.radioValue && "radio" === b && p.nodeName(a, "input")) {
                 var c = a.value;
                 return a.setAttribute("type", b), c && (a.value = c), b
               }
        }
      },
      value: {
        get: function(a, b) {
          return L && p.nodeName(a, "button") ? L.get(a, b) : b in a ? a.value : null
        },
        set: function(a, b, c) {
          return L && p.nodeName(a, "button") ? L.set(a, b, c) : void(a.value = b)
        }
      }
    },
    propFix: {
      tabindex: "tabIndex",
      readonly: "readOnly",
      "for": "htmlFor",
      "class": "className",
      maxlength: "maxLength",
      cellspacing: "cellSpacing",
      cellpadding: "cellPadding",
      rowspan: "rowSpan",
      colspan: "colSpan",
      usemap: "useMap",
      frameborder: "frameBorder",
      contenteditable: "contentEditable"
    },
    prop: function(a, c, d) {
      var e, f, g, h = a.nodeType;
      if (a && 3 !== h && 8 !== h && 2 !== h) return g = 1 !== h || !p.isXMLDoc(a), g && (c = p.propFix[c] || c, f = p.propHooks[c]), d !== b ? f && "set" in f && (e = f.set(a, d, c)) !== b ? e : a[c] = d : f && "get" in f && null !== (e = f.get(a, c)) ? e : a[c]
    },
    propHooks: {
      tabIndex: {
        get: function(a) {
          var c = a.getAttributeNode("tabindex");
          return c && c.specified ? parseInt(c.value, 10) : R.test(a.nodeName) || S.test(a.nodeName) && a.href ? 0 : b
        }
      }
    }
  }), M = {
    get: function(a, c) {
      var d, e = p.prop(a, c);
      return e === !0 || "boolean" != typeof e && (d = a.getAttributeNode(c)) && d.nodeValue !== !1 ? c.toLowerCase() : b
    },
    set: function(a, b, c) {
      var d;
      return b === !1 ? p.removeAttr(a, c) : (d = p.propFix[c] || c, d in a && (a[d] = !0), a.setAttribute(c, c.toLowerCase())), c
    }
  }, U || (N = {
    name: !0,
    id: !0,
    coords: !0
  }, L = p.valHooks.button = {
    get: function(a, c) {
      var d;
      return d = a.getAttributeNode(c), d && (N[c] ? "" !== d.value : d.specified) ? d.value : b
    },
    set: function(a, b, c) {
      var d = a.getAttributeNode(c);
      return d || (d = e.createAttribute(c), a.setAttributeNode(d)), d.value = b + ""
    }
  }, p.each(["width", "height"], function(a, b) {
    p.attrHooks[b] = p.extend(p.attrHooks[b], {
      set: function(a, c) {
        return "" === c ? (a.setAttribute(b, "auto"), c) : void 0
      }
    })
  }), p.attrHooks.contenteditable = {
    get: L.get,
    set: function(a, b, c) {
      "" === b && (b = "false"), L.set(a, b, c)
    }
  }), p.support.hrefNormalized || p.each(["href", "src", "width", "height"], function(a, c) {
    p.attrHooks[c] = p.extend(p.attrHooks[c], {
      get: function(a) {
        var d = a.getAttribute(c, 2);
        return null === d ? b : d
      }
    })
  }), p.support.style || (p.attrHooks.style = {
    get: function(a) {
      return a.style.cssText.toLowerCase() || b
    },
    set: function(a, b) {
      return a.style.cssText = b + ""
    }
  }), p.support.optSelected || (p.propHooks.selected = p.extend(p.propHooks.selected, {
    get: function(a) {
      var b = a.parentNode;
      return b && (b.selectedIndex, b.parentNode && b.parentNode.selectedIndex), null
    }
  })), p.support.enctype || (p.propFix.enctype = "encoding"), p.support.checkOn || p.each(["radio", "checkbox"], function() {
    p.valHooks[this] = {
      get: function(a) {
        return null === a.getAttribute("value") ? "on" : a.value
      }
    }
  }), p.each(["radio", "checkbox"], function() {
    p.valHooks[this] = p.extend(p.valHooks[this], {
      set: function(a, b) {
        return p.isArray(b) ? a.checked = p.inArray(p(a).val(), b) >= 0 : void 0
      }
    })
  });
  var V = /^(?:textarea|input|select)$/i,
  W = /^([^\.]*|)(?:\.(.+)|)$/,
  X = /(?:^|\s)hover(\.\S+|)\b/,
  Y = /^key/,
  Z = /^(?:mouse|contextmenu)|click/,
  $ = /^(?:focusinfocus|focusoutblur)$/,
  _ = function(a) {
    return p.event.special.hover ? a : a.replace(X, "mouseenter$1 mouseleave$1")
  };
  p.event = {
    add: function(a, c, d, e, f) {
      var g, h, i, j, k, l, m, n, o, q, r;
      if (3 !== a.nodeType && 8 !== a.nodeType && c && d && (g = p._data(a))) {
        for (d.handler && (o = d, d = o.handler, f = o.selector), d.guid || (d.guid = p.guid++), i = g.events, i || (g.events = i = {}), h = g.handle, h || (g.handle = h = function(a) {
          return "undefined" == typeof p || a && p.event.triggered === a.type ? b : p.event.dispatch.apply(h.elem, arguments)
        }, h.elem = a), c = p.trim(_(c)).split(" "), j = 0; j < c.length; j++) k = W.exec(c[j]) || [], l = k[1], m = (k[2] || "").split(".").sort(), r = p.event.special[l] || {}, l = (f ? r.delegateType : r.bindType) || l, r = p.event.special[l] || {}, n = p.extend({
          type: l,
          origType: k[1],
          data: e,
          handler: d,
          guid: d.guid,
          selector: f,
          needsContext: f && p.expr.match.needsContext.test(f),
                                                                                                                                                                                                                                                                namespace: m.join(".")
        }, o), q = i[l], q || (q = i[l] = [], q.delegateCount = 0, r.setup && r.setup.call(a, e, m, h) !== !1 || (a.addEventListener ? a.addEventListener(l, h, !1) : a.attachEvent && a.attachEvent("on" + l, h))), r.add && (r.add.call(a, n), n.handler.guid || (n.handler.guid = d.guid)), f ? q.splice(q.delegateCount++, 0, n) : q.push(n), p.event.global[l] = !0;
        a = null
      }
    },
    global: {},
    remove: function(a, b, c, d, e) {
      var f, g, h, i, j, k, l, m, n, o, q, r = p.hasData(a) && p._data(a);
      if (r && (m = r.events)) {
        for (b = p.trim(_(b || "")).split(" "), f = 0; f < b.length; f++)
          if (g = W.exec(b[f]) || [], h = i = g[1], j = g[2], h) {
            for (n = p.event.special[h] || {}, h = (d ? n.delegateType : n.bindType) || h, o = m[h] || [], k = o.length, j = j ? new RegExp("(^|\\.)" + j.split(".").sort().join("\\.(?:.*\\.|)") + "(\\.|$)") : null, l = 0; l < o.length; l++) q = o[l], !(!e && i !== q.origType || c && c.guid !== q.guid || j && !j.test(q.namespace) || d && d !== q.selector && ("**" !== d || !q.selector) || (o.splice(l--, 1), q.selector && o.delegateCount--, !n.remove || !n.remove.call(a, q)));
            0 === o.length && k !== o.length && ((!n.teardown || n.teardown.call(a, j, r.handle) === !1) && p.removeEvent(a, h, r.handle), delete m[h])
          } else
            for (h in m) p.event.remove(a, h + b[f], c, d, !0);
            p.isEmptyObject(m) && (delete r.handle, p.removeData(a, "events", !0))
      }
    },
    customEvent: {
      getData: !0,
      setData: !0,
      changeData: !0
    },
    trigger: function(c, d, f, g) {
      if (!f || 3 !== f.nodeType && 8 !== f.nodeType) {
        var h, i, j, k, l, m, n, o, q, r, s = c.type || c,
        t = [];
        if ($.test(s + p.event.triggered)) return;
        if (s.indexOf("!") >= 0 && (s = s.slice(0, -1), i = !0), s.indexOf(".") >= 0 && (t = s.split("."), s = t.shift(), t.sort()), (!f || p.event.customEvent[s]) && !p.event.global[s]) return;
        if (c = "object" == typeof c ? c[p.expando] ? c : new p.Event(s, c) : new p.Event(s), c.type = s, c.isTrigger = !0, c.exclusive = i, c.namespace = t.join("."), c.namespace_re = c.namespace ? new RegExp("(^|\\.)" + t.join("\\.(?:.*\\.|)") + "(\\.|$)") : null, m = s.indexOf(":") < 0 ? "on" + s : "", !f) {
          h = p.cache;
          for (j in h) h[j].events && h[j].events[s] && p.event.trigger(c, d, h[j].handle.elem, !0);
          return
        }
        if (c.result = b, c.target || (c.target = f), d = null != d ? p.makeArray(d) : [], d.unshift(c), n = p.event.special[s] || {}, n.trigger && n.trigger.apply(f, d) === !1) return;
        if (q = [
          [f, n.bindType || s]
        ], !g && !n.noBubble && !p.isWindow(f)) {
          for (r = n.delegateType || s, k = $.test(r + s) ? f : f.parentNode, l = f; k; k = k.parentNode) q.push([k, r]), l = k;
          l === (f.ownerDocument || e) && q.push([l.defaultView || l.parentWindow || a, r])
        }
        for (j = 0; j < q.length && !c.isPropagationStopped(); j++) k = q[j][0], c.type = q[j][1], o = (p._data(k, "events") || {})[c.type] && p._data(k, "handle"), o && o.apply(k, d), o = m && k[m], o && p.acceptData(k) && o.apply && o.apply(k, d) === !1 && c.preventDefault();
        return c.type = s, !(g || c.isDefaultPrevented() || n._default && n._default.apply(f.ownerDocument, d) !== !1 || "click" === s && p.nodeName(f, "a") || !p.acceptData(f) || !m || !f[s] || ("focus" === s || "blur" === s) && 0 === c.target.offsetWidth || p.isWindow(f) || (l = f[m], l && (f[m] = null), p.event.triggered = s, f[s](), p.event.triggered = b, !l || !(f[m] = l))), c.result
      }
    },
    dispatch: function(c) {
      c = p.event.fix(c || a.event);
      var d, e, f, g, h, i, j, l, m, o = (p._data(this, "events") || {})[c.type] || [],
      q = o.delegateCount,
      r = k.call(arguments),
      s = !c.exclusive && !c.namespace,
      t = p.event.special[c.type] || {},
      u = [];
      if (r[0] = c, c.delegateTarget = this, !t.preDispatch || t.preDispatch.call(this, c) !== !1) {
        if (q && (!c.button || "click" !== c.type))
          for (f = c.target; f != this; f = f.parentNode || this)
            if (f.disabled !== !0 || "click" !== c.type) {
              for (h = {}, j = [], d = 0; q > d; d++) l = o[d], m = l.selector, h[m] === b && (h[m] = l.needsContext ? p(m, this).index(f) >= 0 : p.find(m, this, null, [f]).length), h[m] && j.push(l);
              j.length && u.push({
                elem: f,
                matches: j
              })
            }
            for (o.length > q && u.push({
              elem: this,
              matches: o.slice(q)
            }), d = 0; d < u.length && !c.isPropagationStopped(); d++)
              for (i = u[d], c.currentTarget = i.elem, e = 0; e < i.matches.length && !c.isImmediatePropagationStopped(); e++) l = i.matches[e], (s || !c.namespace && !l.namespace || c.namespace_re && c.namespace_re.test(l.namespace)) && (c.data = l.data, c.handleObj = l, g = ((p.event.special[l.origType] || {}).handle || l.handler).apply(i.elem, r), g !== b && (c.result = g, g === !1 && (c.preventDefault(), c.stopPropagation())));
              return t.postDispatch && t.postDispatch.call(this, c), c.result
      }
    },
    props: "attrChange attrName relatedNode srcElement altKey bubbles cancelable ctrlKey currentTarget eventPhase metaKey relatedTarget shiftKey target timeStamp view which".split(" "),
    fixHooks: {},
    keyHooks: {
      props: "char charCode key keyCode".split(" "),
      filter: function(a, b) {
        return null == a.which && (a.which = null != b.charCode ? b.charCode : b.keyCode), a
      }
    },
    mouseHooks: {
      props: "button buttons clientX clientY fromElement offsetX offsetY pageX pageY screenX screenY toElement".split(" "),
      filter: function(a, c) {
        var d, f, g, h = c.button,
        i = c.fromElement;
        return null == a.pageX && null != c.clientX && (d = a.target.ownerDocument || e, f = d.documentElement, g = d.body, a.pageX = c.clientX + (f && f.scrollLeft || g && g.scrollLeft || 0) - (f && f.clientLeft || g && g.clientLeft || 0), a.pageY = c.clientY + (f && f.scrollTop || g && g.scrollTop || 0) - (f && f.clientTop || g && g.clientTop || 0)), !a.relatedTarget && i && (a.relatedTarget = i === a.target ? c.toElement : i), !a.which && h !== b && (a.which = 1 & h ? 1 : 2 & h ? 3 : 4 & h ? 2 : 0), a
      }
    },
    fix: function(a) {
      if (a[p.expando]) return a;
      var b, c, d = a,
      f = p.event.fixHooks[a.type] || {},
      g = f.props ? this.props.concat(f.props) : this.props;
      for (a = p.Event(d), b = g.length; b;) c = g[--b], a[c] = d[c];
      return a.target || (a.target = d.srcElement || e), 3 === a.target.nodeType && (a.target = a.target.parentNode), a.metaKey = !!a.metaKey, f.filter ? f.filter(a, d) : a
    },
    special: {
      load: {
        noBubble: !0
      },
      focus: {
        delegateType: "focusin"
      },
      blur: {
        delegateType: "focusout"
      },
      beforeunload: {
        setup: function(a, b, c) {
          p.isWindow(this) && (this.onbeforeunload = c)
        },
        teardown: function(a, b) {
          this.onbeforeunload === b && (this.onbeforeunload = null)
        }
      }
    },
    simulate: function(a, b, c, d) {
      var e = p.extend(new p.Event, c, {
        type: a,
        isSimulated: !0,
        originalEvent: {}
      });
      d ? p.event.trigger(e, null, b) : p.event.dispatch.call(b, e), e.isDefaultPrevented() && c.preventDefault()
    }
  }, p.event.handle = p.event.dispatch, p.removeEvent = e.removeEventListener ? function(a, b, c) {
    a.removeEventListener && a.removeEventListener(b, c, !1)
  } : function(a, b, c) {
    var d = "on" + b;
    a.detachEvent && ("undefined" == typeof a[d] && (a[d] = null), a.detachEvent(d, c))
  }, p.Event = function(a, b) {
    return this instanceof p.Event ? (a && a.type ? (this.originalEvent = a, this.type = a.type, this.isDefaultPrevented = a.defaultPrevented || a.returnValue === !1 || a.getPreventDefault && a.getPreventDefault() ? bb : ba) : this.type = a, b && p.extend(this, b), this.timeStamp = a && a.timeStamp || p.now(), this[p.expando] = !0, void 0) : new p.Event(a, b)
  }, p.Event.prototype = {
    preventDefault: function() {
      this.isDefaultPrevented = bb;
      var a = this.originalEvent;
      a && (a.preventDefault ? a.preventDefault() : a.returnValue = !1)
    },
    stopPropagation: function() {
      this.isPropagationStopped = bb;
      var a = this.originalEvent;
      a && (a.stopPropagation && a.stopPropagation(), a.cancelBubble = !0)
    },
    stopImmediatePropagation: function() {
      this.isImmediatePropagationStopped = bb, this.stopPropagation()
    },
    isDefaultPrevented: ba,
    isPropagationStopped: ba,
    isImmediatePropagationStopped: ba
  }, p.each({
    mouseenter: "mouseover",
    mouseleave: "mouseout"
  }, function(a, b) {
    p.event.special[a] = {
      delegateType: b,
      bindType: b,
      handle: function(a) {
        {
          var c, d = this,
          e = a.relatedTarget,
          f = a.handleObj;
          f.selector
        }
        return (!e || e !== d && !p.contains(d, e)) && (a.type = f.origType, c = f.handler.apply(this, arguments), a.type = b), c
      }
    }
  }), p.support.submitBubbles || (p.event.special.submit = {
    setup: function() {
      return p.nodeName(this, "form") ? !1 : void p.event.add(this, "click._submit keypress._submit", function(a) {
        var c = a.target,
        d = p.nodeName(c, "input") || p.nodeName(c, "button") ? c.form : b;
        d && !p._data(d, "_submit_attached") && (p.event.add(d, "submit._submit", function(a) {
          a._submit_bubble = !0
        }), p._data(d, "_submit_attached", !0))
      })
    },
    postDispatch: function(a) {
      a._submit_bubble && (delete a._submit_bubble, this.parentNode && !a.isTrigger && p.event.simulate("submit", this.parentNode, a, !0))
    },
    teardown: function() {
      return p.nodeName(this, "form") ? !1 : void p.event.remove(this, "._submit")
    }
  }), p.support.changeBubbles || (p.event.special.change = {
    setup: function() {
      return V.test(this.nodeName) ? (("checkbox" === this.type || "radio" === this.type) && (p.event.add(this, "propertychange._change", function(a) {
        "checked" === a.originalEvent.propertyName && (this._just_changed = !0)
      }), p.event.add(this, "click._change", function(a) {
        this._just_changed && !a.isTrigger && (this._just_changed = !1), p.event.simulate("change", this, a, !0)
      })), !1) : void p.event.add(this, "beforeactivate._change", function(a) {
        var b = a.target;
        V.test(b.nodeName) && !p._data(b, "_change_attached") && (p.event.add(b, "change._change", function(a) {
          this.parentNode && !a.isSimulated && !a.isTrigger && p.event.simulate("change", this.parentNode, a, !0)
        }), p._data(b, "_change_attached", !0))
      })
    },
    handle: function(a) {
      var b = a.target;
      return this !== b || a.isSimulated || a.isTrigger || "radio" !== b.type && "checkbox" !== b.type ? a.handleObj.handler.apply(this, arguments) : void 0
    },
    teardown: function() {
      return p.event.remove(this, "._change"), !V.test(this.nodeName)
    }
  }), p.support.focusinBubbles || p.each({
    focus: "focusin",
    blur: "focusout"
  }, function(a, b) {
    var c = 0,
    d = function(a) {
      p.event.simulate(b, a.target, p.event.fix(a), !0)
    };
    p.event.special[b] = {
      setup: function() {
        0 === c++ && e.addEventListener(a, d, !0)
      },
      teardown: function() {
        0 === --c && e.removeEventListener(a, d, !0)
      }
    }
  }), p.fn.extend({
    on: function(a, c, d, e, f) {
      var g, h;
      if ("object" == typeof a) {
        "string" != typeof c && (d = d || c, c = b);
        for (h in a) this.on(h, c, d, a[h], f);
                  return this
      }
      if (null == d && null == e ? (e = c, d = c = b) : null == e && ("string" == typeof c ? (e = d, d = b) : (e = d, d = c, c = b)), e === !1) e = ba;
                  else if (!e) return this;
                  return 1 === f && (g = e, e = function(a) {
                    return p().off(a), g.apply(this, arguments)
                  }, e.guid = g.guid || (g.guid = p.guid++)), this.each(function() {
                    p.event.add(this, a, e, d, c)
                  })
    },
    one: function(a, b, c, d) {
      return this.on(a, b, c, d, 1)
    },
    off: function(a, c, d) {
      var e, f;
      if (a && a.preventDefault && a.handleObj) return e = a.handleObj, p(a.delegateTarget).off(e.namespace ? e.origType + "." + e.namespace : e.origType, e.selector, e.handler), this;
                  if ("object" == typeof a) {
                    for (f in a) this.off(f, c, a[f]);
                  return this
                  }
                  return (c === !1 || "function" == typeof c) && (d = c, c = b), d === !1 && (d = ba), this.each(function() {
                    p.event.remove(this, a, d, c)
                  })
    },
    bind: function(a, b, c) {
      return this.on(a, null, b, c)
    },
    unbind: function(a, b) {
      return this.off(a, null, b)
    },
    live: function(a, b, c) {
      return p(this.context).on(a, this.selector, b, c), this
    },
    die: function(a, b) {
      return p(this.context).off(a, this.selector || "**", b), this
    },
    delegate: function(a, b, c, d) {
      return this.on(b, a, c, d)
    },
    undelegate: function(a, b, c) {
      return 1 === arguments.length ? this.off(a, "**") : this.off(b, a || "**", c)
    },
    trigger: function(a, b) {
      return this.each(function() {
        p.event.trigger(a, b, this)
      })
    },
    triggerHandler: function(a, b) {
      return this[0] ? p.event.trigger(a, b, this[0], !0) : void 0
    },
    toggle: function(a) {
      var b = arguments,
      c = a.guid || p.guid++,
      d = 0,
      e = function(c) {
        var e = (p._data(this, "lastToggle" + a.guid) || 0) % d;
        return p._data(this, "lastToggle" + a.guid, e + 1), c.preventDefault(), b[e].apply(this, arguments) || !1
      };
      for (e.guid = c; d < b.length;) b[d++].guid = c;
                  return this.click(e)
    },
    hover: function(a, b) {
      return this.mouseenter(a).mouseleave(b || a)
    }
  }), p.each("blur focus focusin focusout load resize scroll unload click dblclick mousedown mouseup mousemove mouseover mouseout mouseenter mouseleave change select submit keydown keypress keyup error contextmenu".split(" "), function(a, b) {
    p.fn[b] = function(a, c) {
      return null == c && (c = a, a = null), arguments.length > 0 ? this.on(b, null, a, c) : this.trigger(b)
    }, Y.test(b) && (p.event.fixHooks[b] = p.event.keyHooks), Z.test(b) && (p.event.fixHooks[b] = p.event.mouseHooks)
  }),
  function(a, b) {
    function bc(a, b, c, d) {
      c = c || [], b = b || r;
      var e, f, i, j, k = b.nodeType;
      if (!a || "string" != typeof a) return c;
      if (1 !== k && 9 !== k) return [];
      if (i = g(b), !i && !d && (e = P.exec(a)))
        if (j = e[1]) {
          if (9 === k) {
            if (f = b.getElementById(j), !f || !f.parentNode) return c;
            if (f.id === j) return c.push(f), c
          } else if (b.ownerDocument && (f = b.ownerDocument.getElementById(j)) && h(b, f) && f.id === j) return c.push(f), c
        } else {
          if (e[2]) return w.apply(c, x.call(b.getElementsByTagName(a), 0)), c;
          if ((j = e[3]) && _ && b.getElementsByClassName) return w.apply(c, x.call(b.getElementsByClassName(j), 0)), c
        }
        return bp(a.replace(L, "$1"), b, c, d, i)
    }

    function bd(a) {
      return function(b) {
        var c = b.nodeName.toLowerCase();
        return "input" === c && b.type === a
      }
    }

    function be(a) {
      return function(b) {
        var c = b.nodeName.toLowerCase();
        return ("input" === c || "button" === c) && b.type === a
      }
    }

    function bf(a) {
      return z(function(b) {
        return b = +b, z(function(c, d) {
          for (var e, f = a([], c.length, b), g = f.length; g--;) c[e = f[g]] && (c[e] = !(d[e] = c[e]))
        })
      })
    }

    function bg(a, b, c) {
      if (a === b) return c;
      for (var d = a.nextSibling; d;) {
        if (d === b) return -1;
        d = d.nextSibling
      }
      return 1
    }

    function bh(a, b) {
      var c, d, f, g, h, i, j, k = C[o][a];
      if (k) return b ? 0 : k.slice(0);
      for (h = a, i = [], j = e.preFilter; h;) {
        (!c || (d = M.exec(h))) && (d && (h = h.slice(d[0].length)), i.push(f = [])), c = !1, (d = N.exec(h)) && (f.push(c = new q(d.shift())), h = h.slice(c.length), c.type = d[0].replace(L, " "));
        for (g in e.filter)(d = W[g].exec(h)) && (!j[g] || (d = j[g](d, r, !0))) && (f.push(c = new q(d.shift())), h = h.slice(c.length), c.type = g, c.matches = d);
        if (!c) break
      }
      return b ? h.length : h ? bc.error(a) : C(a, i).slice(0)
    }

    function bi(a, b, d) {
      var e = b.dir,
      f = d && "parentNode" === b.dir,
      g = u++;
      return b.first ? function(b, c, d) {
        for (; b = b[e];)
          if (f || 1 === b.nodeType) return a(b, c, d)
      } : function(b, d, h) {
        if (h) {
          for (; b = b[e];)
            if ((f || 1 === b.nodeType) && a(b, d, h)) return b
        } else
          for (var i, j = t + " " + g + " ", k = j + c; b = b[e];)
            if (f || 1 === b.nodeType) {
              if ((i = b[o]) === k) return b.sizset;
              if ("string" == typeof i && 0 === i.indexOf(j)) {
                if (b.sizset) return b
              } else {
                if (b[o] = k, a(b, d, h)) return b.sizset = !0, b;
                b.sizset = !1
              }
            }
      }
    }

    function bj(a) {
      return a.length > 1 ? function(b, c, d) {
        for (var e = a.length; e--;)
          if (!a[e](b, c, d)) return !1;
          return !0
      } : a[0]
    }

    function bk(a, b, c, d, e) {
      for (var f, g = [], h = 0, i = a.length, j = null != b; i > h; h++)(f = a[h]) && (!c || c(f, d, e)) && (g.push(f), j && b.push(h));
      return g
    }

    function bl(a, b, c, d, e, f) {
      return d && !d[o] && (d = bl(d)), e && !e[o] && (e = bl(e, f)), z(function(f, g, h, i) {
        if (!f || !e) {
          var j, k, l, m = [],
          n = [],
          o = g.length,
          p = f || bo(b || "*", h.nodeType ? [h] : h, [], f),
                                                                        q = !a || !f && b ? p : bk(p, m, a, h, i),
                                                                        r = c ? e || (f ? a : o || d) ? [] : g : q;
                                                                        if (c && c(q, r, h, i), d)
                                                                          for (l = bk(r, n), d(l, [], h, i), j = l.length; j--;)(k = l[j]) && (r[n[j]] = !(q[n[j]] = k));
                                                                        if (f)
                                                                          for (j = a && r.length; j--;)(k = r[j]) && (f[m[j]] = !(g[m[j]] = k));
                                                                        else r = bk(r === g ? r.splice(o, r.length) : r), e ? e(null, g, r, i) : w.apply(g, r)
        }
      })
    }

    function bm(a) {
      for (var b, c, d, f = a.length, g = e.relative[a[0].type], h = g || e.relative[" "], i = g ? 1 : 0, j = bi(function(a) {
        return a === b
      }, h, !0), k = bi(function(a) {
        return y.call(b, a) > -1
      }, h, !0), m = [function(a, c, d) {
        return !g && (d || c !== l) || ((b = c).nodeType ? j(a, c, d) : k(a, c, d))
      }]; f > i; i++)
        if (c = e.relative[a[i].type]) m = [bi(bj(m), c)];
        else {
          if (c = e.filter[a[i].type].apply(null, a[i].matches), c[o]) {
            for (d = ++i; f > d && !e.relative[a[d].type]; d++);
            return bl(i > 1 && bj(m), i > 1 && a.slice(0, i - 1).join("").replace(L, "$1"), c, d > i && bm(a.slice(i, d)), f > d && bm(a = a.slice(d)), f > d && a.join(""))
          }
          m.push(c)
        }
        return bj(m)
    }

    function bn(a, b) {
      var d = b.length > 0,
      f = a.length > 0,
      g = function(h, i, j, k, m) {
        var n, o, p, q = [],
        s = 0,
        u = "0",
        x = h && [],
        y = null != m,
        z = l,
        A = h || f && e.find.TAG("*", m && i.parentNode || i),
        B = t += null == z ? 1 : Math.E;
        for (y && (l = i !== r && i, c = g.el); null != (n = A[u]); u++) {
          if (f && n) {
            for (o = 0; p = a[o]; o++)
              if (p(n, i, j)) {
                k.push(n);
                break
              }
              y && (t = B, c = ++g.el)
          }
          d && ((n = !p && n) && s--, h && x.push(n))
        }
        if (s += u, d && u !== s) {
          for (o = 0; p = b[o]; o++) p(x, q, i, j);
          if (h) {
            if (s > 0)
              for (; u--;) !x[u] && !q[u] && (q[u] = v.call(k));
              q = bk(q)
          }
          w.apply(k, q), y && !h && q.length > 0 && s + b.length > 1 && bc.uniqueSort(k)
        }
        return y && (t = B, l = z), x
      };
      return g.el = 0, d ? z(g) : g
    }

    function bo(a, b, c, d) {
      for (var e = 0, f = b.length; f > e; e++) bc(a, b[e], c, d);
      return c
    }

    function bp(a, b, c, d, f) {
      {
        var g, h, j, k, l, m = bh(a);
        m.length
      }
      if (!d && 1 === m.length) {
        if (h = m[0] = m[0].slice(0), h.length > 2 && "ID" === (j = h[0]).type && 9 === b.nodeType && !f && e.relative[h[1].type]) {
          if (b = e.find.ID(j.matches[0].replace(V, ""), b, f)[0], !b) return c;
          a = a.slice(h.shift().length)
        }
        for (g = W.POS.test(a) ? -1 : h.length - 1; g >= 0 && (j = h[g], !e.relative[k = j.type]); g--)
          if ((l = e.find[k]) && (d = l(j.matches[0].replace(V, ""), R.test(h[0].type) && b.parentNode || b, f))) {
            if (h.splice(g, 1), a = d.length && h.join(""), !a) return w.apply(c, x.call(d, 0)), c;
            break
          }
      }
      return i(a, m)(d, b, f, c, R.test(a)), c
    }

    function bq() {}
    var c, d, e, f, g, h, i, j, k, l, m = !0,
    n = "undefined",
    o = ("sizcache" + Math.random()).replace(".", ""),
    q = String,
    r = a.document,
    s = r.documentElement,
    t = 0,
    u = 0,
    v = [].pop,
    w = [].push,
    x = [].slice,
    y = [].indexOf || function(a) {
      for (var b = 0, c = this.length; c > b; b++)
        if (this[b] === a) return b;
        return -1
    },
    z = function(a, b) {
      return a[o] = null == b || b, a
    },
    A = function() {
      var a = {},
      b = [];
      return z(function(c, d) {
        return b.push(c) > e.cacheLength && delete a[b.shift()], a[c] = d
      }, a)
    },
    B = A(),
    C = A(),
    D = A(),
    E = "[\\x20\\t\\r\\n\\f]",
    F = "(?:\\\\.|[-\\w]|[^\\x00-\\xa0])+",
    G = F.replace("w", "w#"),
    H = "([*^$|!~]?=)",
    I = "\\[" + E + "*(" + F + ")" + E + "*(?:" + H + E + "*(?:(['\"])((?:\\\\.|[^\\\\])*?)\\3|(" + G + ")|)|)" + E + "*\\]",
    J = ":(" + F + ")(?:\\((?:(['\"])((?:\\\\.|[^\\\\])*?)\\2|([^()[\\]]*|(?:(?:" + I + ")|[^:]|\\\\.)*|.*))\\)|)",
    K = ":(even|odd|eq|gt|lt|nth|first|last)(?:\\(" + E + "*((?:-\\d)?\\d*)" + E + "*\\)|)(?=[^-]|$)",
    L = new RegExp("^" + E + "+|((?:^|[^\\\\])(?:\\\\.)*)" + E + "+$", "g"),
    M = new RegExp("^" + E + "*," + E + "*"),
    N = new RegExp("^" + E + "*([\\x20\\t\\r\\n\\f>+~])" + E + "*"),
    O = new RegExp(J),
    P = /^(?:#([\w\-]+)|(\w+)|\.([\w\-]+))$/,
    R = /[\x20\t\r\n\f]*[+~]/,
    T = /h\d/i,
    U = /input|select|textarea|button/i,
    V = /\\(?!\\)/g,
    W = {
      ID: new RegExp("^#(" + F + ")"),
      CLASS: new RegExp("^\\.(" + F + ")"),
      NAME: new RegExp("^\\[name=['\"]?(" + F + ")['\"]?\\]"),
      TAG: new RegExp("^(" + F.replace("w", "w*") + ")"),
      ATTR: new RegExp("^" + I),
      PSEUDO: new RegExp("^" + J),
      POS: new RegExp(K, "i"),
      CHILD: new RegExp("^:(only|nth|first|last)-child(?:\\(" + E + "*(even|odd|(([+-]|)(\\d*)n|)" + E + "*(?:([+-]|)" + E + "*(\\d+)|))" + E + "*\\)|)", "i"),
      needsContext: new RegExp("^" + E + "*[>+~]|" + K, "i")
    },
    X = function(a) {
      var b = r.createElement("div");
      try {
        return a(b)
      } catch (c) {
        return !1
      } finally {
        b = null
      }
    },
    Y = X(function(a) {
      return a.appendChild(r.createComment("")), !a.getElementsByTagName("*").length
    }),
    Z = X(function(a) {
      return a.innerHTML = "<a href='#'></a>", a.firstChild && typeof a.firstChild.getAttribute !== n && "#" === a.firstChild.getAttribute("href")
    }),
    $ = X(function(a) {
      a.innerHTML = "<select></select>";
      var b = typeof a.lastChild.getAttribute("multiple");
      return "boolean" !== b && "string" !== b
    }),
    _ = X(function(a) {
      return a.innerHTML = "<div class='hidden e'></div><div class='hidden'></div>", a.getElementsByClassName && a.getElementsByClassName("e").length ? (a.lastChild.className = "e", 2 === a.getElementsByClassName("e").length) : !1
    }),
    ba = X(function(a) {
      a.id = o + 0, a.innerHTML = "<a name='" + o + "'></a><div name='" + o + "'></div>", s.insertBefore(a, s.firstChild);
      var b = r.getElementsByName && r.getElementsByName(o).length === 2 + r.getElementsByName(o + 0).length;
      return d = !r.getElementById(o), s.removeChild(a), b
    });
    try {
      x.call(s.childNodes, 0)[0].nodeType
    } catch (bb) {
      x = function(a) {
        for (var b, c = []; b = this[a]; a++) c.push(b);
        return c
      }
    }
    bc.matches = function(a, b) {
      return bc(a, null, null, b)
    }, bc.matchesSelector = function(a, b) {
      return bc(b, null, null, [a]).length > 0
    }, f = bc.getText = function(a) {
      var b, c = "",
      d = 0,
      e = a.nodeType;
      if (e) {
        if (1 === e || 9 === e || 11 === e) {
          if ("string" == typeof a.textContent) return a.textContent;
          for (a = a.firstChild; a; a = a.nextSibling) c += f(a)
        } else if (3 === e || 4 === e) return a.nodeValue
      } else
        for (; b = a[d]; d++) c += f(b);
        return c
    }, g = bc.isXML = function(a) {
      var b = a && (a.ownerDocument || a).documentElement;
      return b ? "HTML" !== b.nodeName : !1
    }, h = bc.contains = s.contains ? function(a, b) {
      var c = 9 === a.nodeType ? a.documentElement : a,
      d = b && b.parentNode;
      return a === d || !!(d && 1 === d.nodeType && c.contains && c.contains(d))
    } : s.compareDocumentPosition ? function(a, b) {
      return b && !!(16 & a.compareDocumentPosition(b))
    } : function(a, b) {
      for (; b = b.parentNode;)
        if (b === a) return !0;
        return !1
    }, bc.attr = function(a, b) {
      var c, d = g(a);
      return d || (b = b.toLowerCase()), (c = e.attrHandle[b]) ? c(a) : d || $ ? a.getAttribute(b) : (c = a.getAttributeNode(b), c ? "boolean" == typeof a[b] ? a[b] ? b : null : c.specified ? c.value : null : null)
    }, e = bc.selectors = {
      cacheLength: 50,
      createPseudo: z,
      match: W,
      attrHandle: Z ? {} : {
        href: function(a) {
          return a.getAttribute("href", 2)
        },
        type: function(a) {
          return a.getAttribute("type")
        }
      },
      find: {
        ID: d ? function(a, b, c) {
          if (typeof b.getElementById !== n && !c) {
            var d = b.getElementById(a);
            return d && d.parentNode ? [d] : []
          }
        } : function(a, c, d) {
          if (typeof c.getElementById !== n && !d) {
            var e = c.getElementById(a);
            return e ? e.id === a || typeof e.getAttributeNode !== n && e.getAttributeNode("id").value === a ? [e] : b : []
          }
        },
        TAG: Y ? function(a, b) {
          return typeof b.getElementsByTagName !== n ? b.getElementsByTagName(a) : void 0
        } : function(a, b) {
          var c = b.getElementsByTagName(a);
          if ("*" === a) {
            for (var d, e = [], f = 0; d = c[f]; f++) 1 === d.nodeType && e.push(d);
            return e
          }
          return c
        },
        NAME: ba && function(a, b) {
          return typeof b.getElementsByName !== n ? b.getElementsByName(name) : void 0
        },
        CLASS: _ && function(a, b, c) {
          return typeof b.getElementsByClassName === n || c ? void 0 : b.getElementsByClassName(a)
        }
      },
      relative: {
        ">": {
          dir: "parentNode",
          first: !0
        },
        " ": {
          dir: "parentNode"
        },
        "+": {
          dir: "previousSibling",
          first: !0
        },
        "~": {
          dir: "previousSibling"
        }
      },
      preFilter: {
        ATTR: function(a) {
          return a[1] = a[1].replace(V, ""), a[3] = (a[4] || a[5] || "").replace(V, ""), "~=" === a[2] && (a[3] = " " + a[3] + " "), a.slice(0, 4)
        },
        CHILD: function(a) {
          return a[1] = a[1].toLowerCase(), "nth" === a[1] ? (a[2] || bc.error(a[0]), a[3] = +(a[3] ? a[4] + (a[5] || 1) : 2 * ("even" === a[2] || "odd" === a[2])), a[4] = +(a[6] + a[7] || "odd" === a[2])) : a[2] && bc.error(a[0]), a
        },
        PSEUDO: function(a) {
          var b, c;
          return W.CHILD.test(a[0]) ? null : (a[3] ? a[2] = a[3] : (b = a[4]) && (O.test(b) && (c = bh(b, !0)) && (c = b.indexOf(")", b.length - c) - b.length) && (b = b.slice(0, c), a[0] = a[0].slice(0, c)), a[2] = b), a.slice(0, 3))
        }
      },
      filter: {
        ID: d ? function(a) {
          return a = a.replace(V, ""),
          function(b) {
            return b.getAttribute("id") === a
          }
        } : function(a) {
          return a = a.replace(V, ""),
          function(b) {
            var c = typeof b.getAttributeNode !== n && b.getAttributeNode("id");
            return c && c.value === a
          }
        },
        TAG: function(a) {
          return "*" === a ? function() {
            return !0
          } : (a = a.replace(V, "").toLowerCase(), function(b) {
            return b.nodeName && b.nodeName.toLowerCase() === a
          })
        },
        CLASS: function(a) {
          var b = B[o][a];
          return b || (b = B(a, new RegExp("(^|" + E + ")" + a + "(" + E + "|$)"))),
          function(a) {
            return b.test(a.className || typeof a.getAttribute !== n && a.getAttribute("class") || "")
          }
        },
        ATTR: function(a, b, c) {
          return function(d) {
            var f = bc.attr(d, a);
            return null == f ? "!=" === b : b ? (f += "", "=" === b ? f === c : "!=" === b ? f !== c : "^=" === b ? c && 0 === f.indexOf(c) : "*=" === b ? c && f.indexOf(c) > -1 : "$=" === b ? c && f.substr(f.length - c.length) === c : "~=" === b ? (" " + f + " ").indexOf(c) > -1 : "|=" === b ? f === c || f.substr(0, c.length + 1) === c + "-" : !1) : !0
          }
        },
        CHILD: function(a, b, c, d) {
          return "nth" === a ? function(a) {
            var b, e, f = a.parentNode;
            if (1 === c && 0 === d) return !0;
            if (f)
              for (e = 0, b = f.firstChild; b && (1 !== b.nodeType || (e++, a !== b)); b = b.nextSibling);
              return e -= d, e === c || e % c === 0 && e / c >= 0
          } : function(b) {
            var c = b;
            switch (a) {
              case "only":
              case "first":
                for (; c = c.previousSibling;)
                  if (1 === c.nodeType) return !1;
                  if ("first" === a) return !0;
                  c = b;
              case "last":
                for (; c = c.nextSibling;)
                  if (1 === c.nodeType) return !1;
                  return !0
            }
          }
        },
        PSEUDO: function(a, b) {
          var c, d = e.pseudos[a] || e.setFilters[a.toLowerCase()] || bc.error("unsupported pseudo: " + a);
          return d[o] ? d(b) : d.length > 1 ? (c = [a, a, "", b], e.setFilters.hasOwnProperty(a.toLowerCase()) ? z(function(a, c) {
            for (var e, f = d(a, b), g = f.length; g--;) e = y.call(a, f[g]), a[e] = !(c[e] = f[g])
          }) : function(a) {
            return d(a, 0, c)
          }) : d
        }
      },
      pseudos: {
        not: z(function(a) {
          var b = [],
          c = [],
          d = i(a.replace(L, "$1"));
          return d[o] ? z(function(a, b, c, e) {
            for (var f, g = d(a, null, e, []), h = a.length; h--;)(f = g[h]) && (a[h] = !(b[h] = f))
          }) : function(a, e, f) {
            return b[0] = a, d(b, null, f, c), !c.pop()
          }
        }),
        has: z(function(a) {
          return function(b) {
            return bc(a, b).length > 0
          }
        }),
        contains: z(function(a) {
          return function(b) {
            return (b.textContent || b.innerText || f(b)).indexOf(a) > -1
          }
        }),
        enabled: function(a) {
          return a.disabled === !1
        },
        disabled: function(a) {
          return a.disabled === !0
        },
        checked: function(a) {
          var b = a.nodeName.toLowerCase();
          return "input" === b && !!a.checked || "option" === b && !!a.selected
        },
        selected: function(a) {
          return a.parentNode && a.parentNode.selectedIndex, a.selected === !0
        },
        parent: function(a) {
          return !e.pseudos.empty(a)
        },
        empty: function(a) {
          var b;
          for (a = a.firstChild; a;) {
            if (a.nodeName > "@" || 3 === (b = a.nodeType) || 4 === b) return !1;
            a = a.nextSibling
          }
          return !0
        },
        header: function(a) {
          return T.test(a.nodeName)
        },
        text: function(a) {
          var b, c;
          return "input" === a.nodeName.toLowerCase() && "text" === (b = a.type) && (null == (c = a.getAttribute("type")) || c.toLowerCase() === b)
        },
        radio: bd("radio"),
        checkbox: bd("checkbox"),
        file: bd("file"),
        password: bd("password"),
        image: bd("image"),
        submit: be("submit"),
        reset: be("reset"),
        button: function(a) {
          var b = a.nodeName.toLowerCase();
          return "input" === b && "button" === a.type || "button" === b
        },
        input: function(a) {
          return U.test(a.nodeName)
        },
        focus: function(a) {
          var b = a.ownerDocument;
          return !(a !== b.activeElement || b.hasFocus && !b.hasFocus() || !a.type && !a.href)
        },
        active: function(a) {
          return a === a.ownerDocument.activeElement
        },
        first: bf(function() {
          return [0]
        }),
        last: bf(function(a, b) {
          return [b - 1]
        }),
        eq: bf(function(a, b, c) {
          return [0 > c ? c + b : c]
        }),
        even: bf(function(a, b) {
          for (var d = 0; b > d; d += 2) a.push(d);
                 return a
        }),
        odd: bf(function(a, b) {
          for (var d = 1; b > d; d += 2) a.push(d);
                return a
        }),
        lt: bf(function(a, b, c) {
          for (var d = 0 > c ? c + b : c; --d >= 0;) a.push(d);
               return a
        }),
        gt: bf(function(a, b, c) {
          for (var d = 0 > c ? c + b : c; ++d < b;) a.push(d);
               return a
        })
      }
    }, j = s.compareDocumentPosition ? function(a, b) {
      return a === b ? (k = !0, 0) : (a.compareDocumentPosition && b.compareDocumentPosition ? 4 & a.compareDocumentPosition(b) : a.compareDocumentPosition) ? -1 : 1
    } : function(a, b) {
      if (a === b) return k = !0, 0;
      if (a.sourceIndex && b.sourceIndex) return a.sourceIndex - b.sourceIndex;
      var c, d, e = [],
      f = [],
      g = a.parentNode,
      h = b.parentNode,
      i = g;
      if (g === h) return bg(a, b);
      if (!g) return -1;
      if (!h) return 1;
      for (; i;) e.unshift(i), i = i.parentNode;
      for (i = h; i;) f.unshift(i), i = i.parentNode;
      c = e.length, d = f.length;
      for (var j = 0; c > j && d > j; j++)
        if (e[j] !== f[j]) return bg(e[j], f[j]);
        return j === c ? bg(a, f[j], -1) : bg(e[j], b, 1)
    }, [0, 0].sort(j), m = !k, bc.uniqueSort = function(a) {
      var b, c = 1;
      if (k = m, a.sort(j), k)
        for (; b = a[c]; c++) b === a[c - 1] && a.splice(c--, 1);
        return a
    }, bc.error = function(a) {
      throw new Error("Syntax error, unrecognized expression: " + a)
    }, i = bc.compile = function(a, b) {
      var c, d = [],
      e = [],
      f = D[o][a];
      if (!f) {
        for (b || (b = bh(a)), c = b.length; c--;) f = bm(b[c]), f[o] ? d.push(f) : e.push(f);
        f = D(a, bn(e, d))
      }
      return f
    }, r.querySelectorAll && function() {
      var a, b = bp,
      c = /'|\\/g,
      d = /\=[\x20\t\r\n\f]*([^'"\]]*)[\x20\t\r\n\f]*\]/g,
      e = [":focus"],
      f = [":active", ":focus"],
      h = s.matchesSelector || s.mozMatchesSelector || s.webkitMatchesSelector || s.oMatchesSelector || s.msMatchesSelector;
      X(function(a) {
        a.innerHTML = "<select><option selected=''></option></select>", a.querySelectorAll("[selected]").length || e.push("\\[" + E + "*(?:checked|disabled|ismap|multiple|readonly|selected|value)"), a.querySelectorAll(":checked").length || e.push(":checked")
      }), X(function(a) {
        a.innerHTML = "<p test=''></p>", a.querySelectorAll("[test^='']").length && e.push("[*^$]=" + E + "*(?:\"\"|'')"), a.innerHTML = "<input type='hidden'/>", a.querySelectorAll(":enabled").length || e.push(":enabled", ":disabled")
      }), e = new RegExp(e.join("|")), bp = function(a, d, f, g, h) {
        if (!(g || h || e && e.test(a))) {
          var i, j, k = !0,
          l = o,
          m = d,
          n = 9 === d.nodeType && a;
          if (1 === d.nodeType && "object" !== d.nodeName.toLowerCase()) {
            for (i = bh(a), (k = d.getAttribute("id")) ? l = k.replace(c, "\\$&") : d.setAttribute("id", l), l = "[id='" + l + "'] ", j = i.length; j--;) i[j] = l + i[j].join("");
            m = R.test(a) && d.parentNode || d, n = i.join(",")
          }
          if (n) try {
            return w.apply(f, x.call(m.querySelectorAll(n), 0)), f
          } catch (p) {} finally {
            k || d.removeAttribute("id")
          }
        }
        return b(a, d, f, g, h)
      }, h && (X(function(b) {
        a = h.call(b, "div");
        try {
          h.call(b, "[test!='']:sizzle"), f.push("!=", J)
        } catch (c) {}
      }), f = new RegExp(f.join("|")), bc.matchesSelector = function(b, c) {
        if (c = c.replace(d, "='$1']"), !(g(b) || f.test(c) || e && e.test(c))) try {
          var i = h.call(b, c);
          if (i || a || b.document && 11 !== b.document.nodeType) return i
        } catch (j) {}
        return bc(c, null, null, [b]).length > 0
      })
    }(), e.pseudos.nth = e.pseudos.eq, e.filters = bq.prototype = e.pseudos, e.setFilters = new bq, bc.attr = p.attr, p.find = bc, p.expr = bc.selectors, p.expr[":"] = p.expr.pseudos, p.unique = bc.uniqueSort, p.text = bc.getText, p.isXMLDoc = bc.isXML, p.contains = bc.contains
  }(a);
  var bc = /Until$/,
  bd = /^(?:parents|prev(?:Until|All))/,
  be = /^.[^:#\[\.,]*$/,
  bf = p.expr.match.needsContext,
  bg = {
    children: !0,
    contents: !0,
    next: !0,
    prev: !0
  };
  p.fn.extend({
    find: function(a) {
      var b, c, d, e, f, g, h = this;
      if ("string" != typeof a) return p(a).filter(function() {
        for (b = 0, c = h.length; c > b; b++)
          if (p.contains(h[b], this)) return !0
      });
      for (g = this.pushStack("", "find", a), b = 0, c = this.length; c > b; b++)
        if (d = g.length, p.find(a, this[b], g), b > 0)
          for (e = d; e < g.length; e++)
            for (f = 0; d > f; f++)
              if (g[f] === g[e]) {
                g.splice(e--, 1);
                break
              }
              return g
    },
    has: function(a) {
      var b, c = p(a, this),
              d = c.length;
              return this.filter(function() {
                for (b = 0; d > b; b++)
                  if (p.contains(this, c[b])) return !0
              })
    },
    not: function(a) {
      return this.pushStack(bj(this, a, !1), "not", a)
    },
    filter: function(a) {
      return this.pushStack(bj(this, a, !0), "filter", a)
    },
    is: function(a) {
      return !!a && ("string" == typeof a ? bf.test(a) ? p(a, this.context).index(this[0]) >= 0 : p.filter(a, this).length > 0 : this.filter(a).length > 0)
    },
    closest: function(a, b) {
      for (var c, d = 0, e = this.length, f = [], g = bf.test(a) || "string" != typeof a ? p(a, b || this.context) : 0; e > d; d++)
        for (c = this[d]; c && c.ownerDocument && c !== b && 11 !== c.nodeType;) {
          if (g ? g.index(c) > -1 : p.find.matchesSelector(c, a)) {
            f.push(c);
            break
          }
          c = c.parentNode
        }
        return f = f.length > 1 ? p.unique(f) : f, this.pushStack(f, "closest", a)
    },
    index: function(a) {
      return a ? "string" == typeof a ? p.inArray(this[0], p(a)) : p.inArray(a.jquery ? a[0] : a, this) : this[0] && this[0].parentNode ? this.prevAll().length : -1
    },
    add: function(a, b) {
      var c = "string" == typeof a ? p(a, b) : p.makeArray(a && a.nodeType ? [a] : a),
              d = p.merge(this.get(), c);
              return this.pushStack(bh(c[0]) || bh(d[0]) ? d : p.unique(d))
    },
    addBack: function(a) {
      return this.add(null == a ? this.prevObject : this.prevObject.filter(a))
    }
  }), p.fn.andSelf = p.fn.addBack, p.each({
    parent: function(a) {
      var b = a.parentNode;
      return b && 11 !== b.nodeType ? b : null
    },
    parents: function(a) {
      return p.dir(a, "parentNode")
    },
    parentsUntil: function(a, b, c) {
      return p.dir(a, "parentNode", c)
    },
    next: function(a) {
      return bi(a, "nextSibling")
    },
    prev: function(a) {
      return bi(a, "previousSibling")
    },
    nextAll: function(a) {
      return p.dir(a, "nextSibling")
    },
    prevAll: function(a) {
      return p.dir(a, "previousSibling")
    },
    nextUntil: function(a, b, c) {
      return p.dir(a, "nextSibling", c)
    },
    prevUntil: function(a, b, c) {
      return p.dir(a, "previousSibling", c)
    },
    siblings: function(a) {
      return p.sibling((a.parentNode || {}).firstChild, a)
    },
    children: function(a) {
      return p.sibling(a.firstChild)
    },
    contents: function(a) {
      return p.nodeName(a, "iframe") ? a.contentDocument || a.contentWindow.document : p.merge([], a.childNodes)
    }
  }, function(a, b) {
    p.fn[a] = function(c, d) {
      var e = p.map(this, b, c);
      return bc.test(a) || (d = c), d && "string" == typeof d && (e = p.filter(d, e)), e = this.length > 1 && !bg[a] ? p.unique(e) : e, this.length > 1 && bd.test(a) && (e = e.reverse()), this.pushStack(e, a, k.call(arguments).join(","))
    }
  }), p.extend({
    filter: function(a, b, c) {
      return c && (a = ":not(" + a + ")"), 1 === b.length ? p.find.matchesSelector(b[0], a) ? [b[0]] : [] : p.find.matches(a, b)
    },
    dir: function(a, c, d) {
      for (var e = [], f = a[c]; f && 9 !== f.nodeType && (d === b || 1 !== f.nodeType || !p(f).is(d));) 1 === f.nodeType && e.push(f), f = f[c];
               return e
    },
    sibling: function(a, b) {
      for (var c = []; a; a = a.nextSibling) 1 === a.nodeType && a !== b && c.push(a);
               return c
    }
  });
  var bl = "abbr|article|aside|audio|bdi|canvas|data|datalist|details|figcaption|figure|footer|header|hgroup|mark|meter|nav|output|progress|section|summary|time|video",
  bm = / jQuery\d+="(?:null|\d+)"/g,
  bn = /^\s+/,
  bo = /<(?!area|br|col|embed|hr|img|input|link|meta|param)(([\w:]+)[^>]*)\/>/gi,
  bp = /<([\w:]+)/,
  bq = /<tbody/i,
  br = /<|&#?\w+;/,
  bs = /<(?:script|style|link)/i,
  bt = /<(?:script|object|embed|option|style)/i,
  bu = new RegExp("<(?:" + bl + ")[\\s/>]", "i"),
  bv = /^(?:checkbox|radio)$/,
  bw = /checked\s*(?:[^=]|=\s*.checked.)/i,
  bx = /\/(java|ecma)script/i,
  by = /^\s*<!(?:\[CDATA\[|\-\-)|[\]\-]{2}>\s*$/g,
  bz = {
    option: [1, "<select multiple='multiple'>", "</select>"],
    legend: [1, "<fieldset>", "</fieldset>"],
    thead: [1, "<table>", "</table>"],
    tr: [2, "<table><tbody>", "</tbody></table>"],
    td: [3, "<table><tbody><tr>", "</tr></tbody></table>"],
    col: [2, "<table><tbody></tbody><colgroup>", "</colgroup></table>"],
    area: [1, "<map>", "</map>"],
    _default: [0, "", ""]
  },
  bA = bk(e),
  bB = bA.appendChild(e.createElement("div"));
  bz.optgroup = bz.option, bz.tbody = bz.tfoot = bz.colgroup = bz.caption = bz.thead, bz.th = bz.td, p.support.htmlSerialize || (bz._default = [1, "X<div>", "</div>"]), p.fn.extend({
    text: function(a) {
      return p.access(this, function(a) {
        return a === b ? p.text(this) : this.empty().append((this[0] && this[0].ownerDocument || e).createTextNode(a))
      }, null, a, arguments.length)
    },
    wrapAll: function(a) {
      if (p.isFunction(a)) return this.each(function(b) {
        p(this).wrapAll(a.call(this, b))
      });
      if (this[0]) {
        var b = p(a, this[0].ownerDocument).eq(0).clone(!0);
        this[0].parentNode && b.insertBefore(this[0]), b.map(function() {
          for (var a = this; a.firstChild && 1 === a.firstChild.nodeType;) a = a.firstChild;
                                                             return a
        }).append(this)
      }
      return this
    },
    wrapInner: function(a) {
      return this.each(p.isFunction(a) ? function(b) {
        p(this).wrapInner(a.call(this, b))
      } : function() {
        var b = p(this),
                       c = b.contents();
                       c.length ? c.wrapAll(a) : b.append(a)
      })
    },
    wrap: function(a) {
      var b = p.isFunction(a);
      return this.each(function(c) {
        p(this).wrapAll(b ? a.call(this, c) : a)
      })
    },
    unwrap: function() {
      return this.parent().each(function() {
        p.nodeName(this, "body") || p(this).replaceWith(this.childNodes)
      }).end()
    },
    append: function() {
      return this.domManip(arguments, !0, function(a) {
        (1 === this.nodeType || 11 === this.nodeType) && this.appendChild(a)
      })
    },
    prepend: function() {
      return this.domManip(arguments, !0, function(a) {
        (1 === this.nodeType || 11 === this.nodeType) && this.insertBefore(a, this.firstChild)
      })
    },
    before: function() {
      if (!bh(this[0])) return this.domManip(arguments, !1, function(a) {
        this.parentNode.insertBefore(a, this)
      });
      if (arguments.length) {
        var a = p.clean(arguments);
        return this.pushStack(p.merge(a, this), "before", this.selector)
      }
    },
    after: function() {
      if (!bh(this[0])) return this.domManip(arguments, !1, function(a) {
        this.parentNode.insertBefore(a, this.nextSibling)
      });
      if (arguments.length) {
        var a = p.clean(arguments);
        return this.pushStack(p.merge(this, a), "after", this.selector)
      }
    },
    remove: function(a, b) {
      for (var c, d = 0; null != (c = this[d]); d++)(!a || p.filter(a, [c]).length) && (!b && 1 === c.nodeType && (p.cleanData(c.getElementsByTagName("*")), p.cleanData([c])), c.parentNode && c.parentNode.removeChild(c));
                                                                                                                                                                                     return this
    },
    empty: function() {
      for (var a, b = 0; null != (a = this[b]); b++)
        for (1 === a.nodeType && p.cleanData(a.getElementsByTagName("*")); a.firstChild;) a.removeChild(a.firstChild);
                                                                                                                                                                                     return this
    },
    clone: function(a, b) {
      return a = null == a ? !1 : a, b = null == b ? a : b, this.map(function() {
        return p.clone(this, a, b)
      })
    },
    html: function(a) {
      return p.access(this, function(a) {
        var c = this[0] || {},
        d = 0,
        e = this.length;
        if (a === b) return 1 === c.nodeType ? c.innerHTML.replace(bm, "") : b;
                      if (!("string" != typeof a || bs.test(a) || !p.support.htmlSerialize && bu.test(a) || !p.support.leadingWhitespace && bn.test(a) || bz[(bp.exec(a) || ["", ""])[1].toLowerCase()])) {
                        a = a.replace(bo, "<$1></$2>");
                        try {
                          for (; e > d; d++) c = this[d] || {}, 1 === c.nodeType && (p.cleanData(c.getElementsByTagName("*")), c.innerHTML = a);
                      c = 0
                        } catch (f) {}
                      }
                      c && this.empty().append(a)
      }, null, a, arguments.length)
    },
    replaceWith: function(a) {
      return bh(this[0]) ? this.length ? this.pushStack(p(p.isFunction(a) ? a() : a), "replaceWith", a) : this : p.isFunction(a) ? this.each(function(b) {
        var c = p(this),
                                                                                                                                             d = c.html();
                                                                                                                                             c.replaceWith(a.call(this, b, d))
      }) : ("string" != typeof a && (a = p(a).detach()), this.each(function() {
        var b = this.nextSibling,
        c = this.parentNode;
        p(this).remove(), b ? p(b).before(a) : p(c).append(a)
      }))
    },
    detach: function(a) {
      return this.remove(a, !0)
    },
    domManip: function(a, c, d) {
      a = [].concat.apply([], a);
      var e, f, g, h, i = 0,
      j = a[0],
      k = [],
      l = this.length;
      if (!p.support.checkClone && l > 1 && "string" == typeof j && bw.test(j)) return this.each(function() {
        p(this).domManip(a, c, d)
      });
      if (p.isFunction(j)) return this.each(function(e) {
        var f = p(this);
        a[0] = j.call(this, e, c ? f.html() : b), f.domManip(a, c, d)
      });
      if (this[0]) {
        if (e = p.buildFragment(a, this, k), g = e.fragment, f = g.firstChild, 1 === g.childNodes.length && (g = f), f)
          for (c = c && p.nodeName(f, "tr"), h = e.cacheable || l - 1; l > i; i++) d.call(c && p.nodeName(this[i], "table") ? bC(this[i], "tbody") : this[i], i === h ? g : p.clone(g, !0, !0));
                                                                                                                                                                                     g = f = null, k.length && p.each(k, function(a, b) {
                                                                                                                                                                                       b.src ? p.ajax ? p.ajax({
                                                                                                                                                                                         url: b.src,
                                                                                                                                                                                         type: "GET",
                                                                                                                                                                                         dataType: "script",
                                                                                                                                                                                         async: !1,
                                                                                                                                                                                         global: !1,
                                                                                                                                                                                         "throws": !0
                                                                                                                                                                                       }) : p.error("no ajax") : p.globalEval((b.text || b.textContent || b.innerHTML || "").replace(by, "")), b.parentNode && b.parentNode.removeChild(b)
                                                                                                                                                                                     })
      }
      return this
    }
  }), p.buildFragment = function(a, c, d) {
    var f, g, h, i = a[0];
    return c = c || e, c = !c.nodeType && c[0] || c, c = c.ownerDocument || c, 1 === a.length && "string" == typeof i && i.length < 512 && c === e && "<" === i.charAt(0) && !bt.test(i) && (p.support.checkClone || !bw.test(i)) && (p.support.html5Clone || !bu.test(i)) && (g = !0, f = p.fragments[i], h = f !== b), f || (f = c.createDocumentFragment(), p.clean(a, c, f, d), g && (p.fragments[i] = h && f)), {
      fragment: f,
      cacheable: g
    }
  }, p.fragments = {}, p.each({
    appendTo: "append",
    prependTo: "prepend",
    insertBefore: "before",
    insertAfter: "after",
    replaceAll: "replaceWith"
  }, function(a, b) {
    p.fn[a] = function(c) {
      var d, e = 0,
      f = [],
      g = p(c),
                              h = g.length,
                              i = 1 === this.length && this[0].parentNode;
                              if ((null == i || i && 11 === i.nodeType && 1 === i.childNodes.length) && 1 === h) return g[b](this[0]), this;
                              for (; h > e; e++) d = (e > 0 ? this.clone(!0) : this).get(), p(g[e])[b](d), f = f.concat(d);
                              return this.pushStack(f, a, g.selector)
    }
  }), p.extend({
    clone: function(a, b, c) {
      var d, e, f, g;
      if (p.support.html5Clone || p.isXMLDoc(a) || !bu.test("<" + a.nodeName + ">") ? g = a.cloneNode(!0) : (bB.innerHTML = a.outerHTML, bB.removeChild(g = bB.firstChild)), !(p.support.noCloneEvent && p.support.noCloneChecked || 1 !== a.nodeType && 11 !== a.nodeType || p.isXMLDoc(a)))
        for (bE(a, g), d = bF(a), e = bF(g), f = 0; d[f]; ++f) e[f] && bE(d[f], e[f]);
               if (b && (bD(a, g), c))
                 for (d = bF(a), e = bF(g), f = 0; d[f]; ++f) bD(d[f], e[f]);
               return d = e = null, g
    },
    clean: function(a, b, c, d) {
      var f, g, h, i, j, k, l, m, n, q, r, s = b === e && bA,
      t = [];
      for (b && "undefined" != typeof b.createDocumentFragment || (b = e), f = 0; null != (h = a[f]); f++)
        if ("number" == typeof h && (h += ""), h) {
          if ("string" == typeof h)
            if (br.test(h)) {
              for (s = s || bk(b), l = b.createElement("div"), s.appendChild(l), h = h.replace(bo, "<$1></$2>"), i = (bp.exec(h) || ["", ""])[1].toLowerCase(), j = bz[i] || bz._default, k = j[0], l.innerHTML = j[1] + h + j[2]; k--;) l = l.lastChild;
               if (!p.support.tbody)
                 for (m = bq.test(h), n = "table" !== i || m ? "<table>" !== j[1] || m ? [] : l.childNodes : l.firstChild && l.firstChild.childNodes, g = n.length - 1; g >= 0; --g) p.nodeName(n[g], "tbody") && !n[g].childNodes.length && n[g].parentNode.removeChild(n[g]);
               !p.support.leadingWhitespace && bn.test(h) && l.insertBefore(b.createTextNode(bn.exec(h)[0]), l.firstChild), h = l.childNodes, l.parentNode.removeChild(l)
            } else h = b.createTextNode(h);
               h.nodeType ? t.push(h) : p.merge(t, h)
        }
        if (l && (h = l = s = null), !p.support.appendChecked)
          for (f = 0; null != (h = t[f]); f++) p.nodeName(h, "input") ? bG(h) : "undefined" != typeof h.getElementsByTagName && p.grep(h.getElementsByTagName("input"), bG);
               if (c)
                 for (q = function(a) {
                   return !a.type || bx.test(a.type) ? d ? d.push(a.parentNode ? a.parentNode.removeChild(a) : a) : c.appendChild(a) : void 0
                 }, f = 0; null != (h = t[f]); f++) p.nodeName(h, "script") && q(h) || (c.appendChild(h), "undefined" != typeof h.getElementsByTagName && (r = p.grep(p.merge([], h.getElementsByTagName("script")), q), t.splice.apply(t, [f + 1, 0].concat(r)), f += r.length));
               return t
    },
    cleanData: function(a, b) {
      for (var c, d, e, f, g = 0, h = p.expando, i = p.cache, j = p.support.deleteExpando, k = p.event.special; null != (e = a[g]); g++)
        if ((b || p.acceptData(e)) && (d = e[h], c = d && i[d])) {
          if (c.events)
            for (f in c.events) k[f] ? p.event.remove(e, f) : p.removeEvent(e, f, c.handle);
               i[d] && (delete i[d], j ? delete e[h] : e.removeAttribute ? e.removeAttribute(h) : e[h] = null, p.deletedIds.push(d))
        }
    }
  }),
  function() {
    var a, b;
    p.uaMatch = function(a) {
      a = a.toLowerCase();
      var b = /(chrome)[ \/]([\w.]+)/.exec(a) || /(webkit)[ \/]([\w.]+)/.exec(a) || /(opera)(?:.*version|)[ \/]([\w.]+)/.exec(a) || /(msie) ([\w.]+)/.exec(a) || a.indexOf("compatible") < 0 && /(mozilla)(?:.*? rv:([\w.]+)|)/.exec(a) || [];
      return {
        browser: b[1] || "",
        version: b[2] || "0"
      }
    }, a = p.uaMatch(g.userAgent), b = {}, a.browser && (b[a.browser] = !0, b.version = a.version), b.chrome ? b.webkit = !0 : b.webkit && (b.safari = !0), p.browser = b, p.sub = function() {
      function a(b, c) {
        return new a.fn.init(b, c)
      }
      p.extend(!0, a, this), a.superclass = this, a.fn = a.prototype = this(), a.fn.constructor = a, a.sub = this.sub, a.fn.init = function c(c, d) {
        return d && d instanceof p && !(d instanceof a) && (d = a(d)), p.fn.init.call(this, c, d, b)
      }, a.fn.init.prototype = a.fn;
      var b = a(e);
      return a
    }
  }();
  var bH, bI, bJ, bK = /alpha\([^)]*\)/i,
  bL = /opacity=([^)]*)/,
  bM = /^(top|right|bottom|left)$/,
  bN = /^(none|table(?!-c[ea]).+)/,
  bO = /^margin/,
  bP = new RegExp("^(" + q + ")(.*)$", "i"),
  bQ = new RegExp("^(" + q + ")(?!px)[a-z%]+$", "i"),
  bR = new RegExp("^([-+])=(" + q + ")", "i"),
  bS = {},
  bT = {
    position: "absolute",
    visibility: "hidden",
    display: "block"
  },
  bU = {
    letterSpacing: 0,
    fontWeight: 400
  },
  bV = ["Top", "Right", "Bottom", "Left"],
  bW = ["Webkit", "O", "Moz", "ms"],
  bX = p.fn.toggle;
  p.fn.extend({
    css: function(a, c) {
      return p.access(this, function(a, c, d) {
        return d !== b ? p.style(a, c, d) : p.css(a, c)
      }, a, c, arguments.length > 1)
    },
    show: function() {
      return b$(this, !0)
    },
    hide: function() {
      return b$(this)
    },
    toggle: function(a, b) {
      var c = "boolean" == typeof a;
      return p.isFunction(a) && p.isFunction(b) ? bX.apply(this, arguments) : this.each(function() {
        (c ? a : bZ(this)) ? p(this).show(): p(this).hide()
      })
    }
  }), p.extend({
    cssHooks: {
      opacity: {
        get: function(a, b) {
          if (b) {
            var c = bH(a, "opacity");
            return "" === c ? "1" : c
          }
        }
      }
    },
    cssNumber: {
      fillOpacity: !0,
      fontWeight: !0,
      lineHeight: !0,
      opacity: !0,
      orphans: !0,
      widows: !0,
      zIndex: !0,
      zoom: !0
    },
    cssProps: {
      "float": p.support.cssFloat ? "cssFloat" : "styleFloat"
    },
    style: function(a, c, d, e) {
      if (a && 3 !== a.nodeType && 8 !== a.nodeType && a.style) {
        var f, g, h, i = p.camelCase(c),
               j = a.style;
               if (c = p.cssProps[i] || (p.cssProps[i] = bY(j, i)), h = p.cssHooks[c] || p.cssHooks[i], d === b) return h && "get" in h && (f = h.get(a, !1, e)) !== b ? f : j[c];
               if (g = typeof d, "string" === g && (f = bR.exec(d)) && (d = (f[1] + 1) * f[2] + parseFloat(p.css(a, c)), g = "number"), !(null == d || "number" === g && isNaN(d) || ("number" === g && !p.cssNumber[i] && (d += "px"), h && "set" in h && (d = h.set(a, d, e)) === b))) try {
                 j[c] = d
               } catch (k) {}
      }
    },
    css: function(a, c, d, e) {
      var f, g, h, i = p.camelCase(c);
      return c = p.cssProps[i] || (p.cssProps[i] = bY(a.style, i)), h = p.cssHooks[c] || p.cssHooks[i], h && "get" in h && (f = h.get(a, !0, e)), f === b && (f = bH(a, c)), "normal" === f && c in bU && (f = bU[c]), d || e !== b ? (g = parseFloat(f), d || p.isNumeric(g) ? g || 0 : f) : f
    },
    swap: function(a, b, c) {
      var d, e, f = {};
      for (e in b) f[e] = a.style[e], a.style[e] = b[e];
               d = c.call(a);
      for (e in b) a.style[e] = f[e];
               return d
    }
  }), a.getComputedStyle ? bH = function(b, c) {
    var d, e, f, g, h = a.getComputedStyle(b, null),
    i = b.style;
    return h && (d = h[c], "" === d && !p.contains(b.ownerDocument, b) && (d = p.style(b, c)), bQ.test(d) && bO.test(c) && (e = i.width, f = i.minWidth, g = i.maxWidth, i.minWidth = i.maxWidth = i.width = d, d = h.width, i.width = e, i.minWidth = f, i.maxWidth = g)), d
  } : e.documentElement.currentStyle && (bH = function(a, b) {
    var c, d, e = a.currentStyle && a.currentStyle[b],
    f = a.style;
    return null == e && f && f[b] && (e = f[b]), bQ.test(e) && !bM.test(b) && (c = f.left, d = a.runtimeStyle && a.runtimeStyle.left, d && (a.runtimeStyle.left = a.currentStyle.left), f.left = "fontSize" === b ? "1em" : e, e = f.pixelLeft + "px", f.left = c, d && (a.runtimeStyle.left = d)), "" === e ? "auto" : e
  }), p.each(["height", "width"], function(a, b) {
    p.cssHooks[b] = {
      get: function(a, c, d) {
        return c ? 0 === a.offsetWidth && bN.test(bH(a, "display")) ? p.swap(a, bT, function() {
          return cb(a, b, d)
        }) : cb(a, b, d) : void 0
      },
      set: function(a, c, d) {
        return b_(a, c, d ? ca(a, b, d, p.support.boxSizing && "border-box" === p.css(a, "boxSizing")) : 0)
      }
    }
  }), p.support.opacity || (p.cssHooks.opacity = {
    get: function(a, b) {
      return bL.test((b && a.currentStyle ? a.currentStyle.filter : a.style.filter) || "") ? .01 * parseFloat(RegExp.$1) + "" : b ? "1" : ""
    },
    set: function(a, b) {
      var c = a.style,
      d = a.currentStyle,
      e = p.isNumeric(b) ? "alpha(opacity=" + 100 * b + ")" : "",
                            f = d && d.filter || c.filter || "";
                            c.zoom = 1, b >= 1 && "" === p.trim(f.replace(bK, "")) && c.removeAttribute && (c.removeAttribute("filter"), d && !d.filter) || (c.filter = bK.test(f) ? f.replace(bK, e) : f + " " + e)
    }
  }), p(function() {
    p.support.reliableMarginRight || (p.cssHooks.marginRight = {
      get: function(a, b) {
        return p.swap(a, {
          display: "inline-block"
        }, function() {
          return b ? bH(a, "marginRight") : void 0
        })
      }
    }), !p.support.pixelPosition && p.fn.position && p.each(["top", "left"], function(a, b) {
      p.cssHooks[b] = {
        get: function(a, c) {
          if (c) {
            var d = bH(a, b);
            return bQ.test(d) ? p(a).position()[b] + "px" : d
          }
        }
      }
    })
  }), p.expr && p.expr.filters && (p.expr.filters.hidden = function(a) {
    return 0 === a.offsetWidth && 0 === a.offsetHeight || !p.support.reliableHiddenOffsets && "none" === (a.style && a.style.display || bH(a, "display"))
  }, p.expr.filters.visible = function(a) {
    return !p.expr.filters.hidden(a)
  }), p.each({
    margin: "",
    padding: "",
    border: "Width"
  }, function(a, b) {
    p.cssHooks[a + b] = {
      expand: function(c) {
        var d, e = "string" == typeof c ? c.split(" ") : [c],
             f = {};
             for (d = 0; 4 > d; d++) f[a + bV[d] + b] = e[d] || e[d - 2] || e[0];
             return f
      }
    }, bO.test(a) || (p.cssHooks[a + b].set = b_)
  });
  var cd = /%20/g,
  ce = /\[\]$/,
  cf = /\r?\n/g,
  cg = /^(?:color|date|datetime|datetime-local|email|hidden|month|number|password|range|search|tel|text|time|url|week)$/i,
  ch = /^(?:select|textarea)/i;
  p.fn.extend({
    serialize: function() {
      return p.param(this.serializeArray())
    },
    serializeArray: function() {
      return this.map(function() {
        return this.elements ? p.makeArray(this.elements) : this
      }).filter(function() {
        return this.name && !this.disabled && (this.checked || ch.test(this.nodeName) || cg.test(this.type))
      }).map(function(a, b) {
        var c = p(this).val();
        return null == c ? null : p.isArray(c) ? p.map(c, function(a) {
          return {
            name: b.name,
            value: a.replace(cf, "\r\n")
          }
        }) : {
          name: b.name,
          value: c.replace(cf, "\r\n")
        }
      }).get()
    }
  }), p.param = function(a, c) {
    var d, e = [],
    f = function(a, b) {
      b = p.isFunction(b) ? b() : null == b ? "" : b, e[e.length] = encodeURIComponent(a) + "=" + encodeURIComponent(b)
    };
    if (c === b && (c = p.ajaxSettings && p.ajaxSettings.traditional), p.isArray(a) || a.jquery && !p.isPlainObject(a)) p.each(a, function() {
      f(this.name, this.value)
    });
    else
      for (d in a) ci(d, a[d], c, f);
      return e.join("&").replace(cd, "+")
  };
  var cj, ck, cl = /#.*$/,
  cm = /^(.*?):[ \t]*([^\r\n]*)\r?$/gm,
  cn = /^(?:about|app|app\-storage|.+\-extension|file|res|widget):$/,
  co = /^(?:GET|HEAD)$/,
  cp = /^\/\//,
  cq = /\?/,
  cr = /<script\b[^<]*(?:(?!<\/script>)<[^<]*)*<\/script>/gi,
  cs = /([?&])_=[^&]*/,
  ct = /^([\w\+\.\-]+:)(?:\/\/([^\/?#:]*)(?::(\d+)|)|)/,
  cu = p.fn.load,
  cv = {},
  cw = {},
  cx = ["*/"] + ["*"];
  try {
    ck = f.href
  } catch (cy) {
    ck = e.createElement("a"), ck.href = "", ck = ck.href
  }
  cj = ct.exec(ck.toLowerCase()) || [], p.fn.load = function(a, c, d) {
    if ("string" != typeof a && cu) return cu.apply(this, arguments);
    if (!this.length) return this;
    var e, f, g, h = this,
    i = a.indexOf(" ");
    return i >= 0 && (e = a.slice(i, a.length), a = a.slice(0, i)), p.isFunction(c) ? (d = c, c = b) : c && "object" == typeof c && (f = "POST"), p.ajax({
      url: a,
      type: f,
      dataType: "html",
      data: c,
      complete: function(a, b) {
        d && h.each(d, g || [a.responseText, b, a])
      }
    }).done(function(a) {
      g = arguments, h.html(e ? p("<div>").append(a.replace(cr, "")).find(e) : a)
    }), this
  }, p.each("ajaxStart ajaxStop ajaxComplete ajaxError ajaxSuccess ajaxSend".split(" "), function(a, b) {
    p.fn[b] = function(a) {
      return this.on(b, a)
    }
  }), p.each(["get", "post"], function(a, c) {
    p[c] = function(a, d, e, f) {
      return p.isFunction(d) && (f = f || e, e = d, d = b), p.ajax({
        type: c,
        url: a,
        data: d,
        success: e,
        dataType: f
      })
    }
  }), p.extend({
    getScript: function(a, c) {
      return p.get(a, b, c, "script")
    },
    getJSON: function(a, b, c) {
      return p.get(a, b, c, "json")
    },
    ajaxSetup: function(a, b) {
      return b ? cB(a, p.ajaxSettings) : (b = a, a = p.ajaxSettings), cB(a, b), a
    },
    ajaxSettings: {
      url: ck,
      isLocal: cn.test(cj[1]),
               global: !0,
               type: "GET",
               contentType: "application/x-www-form-urlencoded; charset=UTF-8",
               processData: !0,
               async: !0,
               accepts: {
                 xml: "application/xml, text/xml",
               html: "text/html",
               text: "text/plain",
               json: "application/json, text/javascript",
               "*": cx
               },
               contents: {
                 xml: /xml/,
               html: /html/,
               json: /json/
               },
               responseFields: {
                 xml: "responseXML",
               text: "responseText"
               },
               converters: {
                 "* text": a.String,
               "text html": !0,
               "text json": p.parseJSON,
               "text xml": p.parseXML
               },
               flatOptions: {
                 context: !0,
               url: !0
               }
    },
    ajaxPrefilter: cz(cv),
               ajaxTransport: cz(cw),
               ajax: function(a, c) {
                 function y(a, c, f, i) {
                   var k, s, t, u, w, y = c;
                   2 !== v && (v = 2, h && clearTimeout(h), g = b, e = i || "", x.readyState = a > 0 ? 4 : 0, f && (u = cC(l, x, f)), a >= 200 && 300 > a || 304 === a ? (l.ifModified && (w = x.getResponseHeader("Last-Modified"), w && (p.lastModified[d] = w), w = x.getResponseHeader("Etag"), w && (p.etag[d] = w)), 304 === a ? (y = "notmodified", k = !0) : (k = cD(l, u), y = k.state, s = k.data, t = k.error, k = !t)) : (t = y, (!y || a) && (y = "error", 0 > a && (a = 0))), x.status = a, x.statusText = (c || y) + "", k ? o.resolveWith(m, [s, y, x]) : o.rejectWith(m, [x, y, t]), x.statusCode(r), r = b, j && n.trigger("ajax" + (k ? "Success" : "Error"), [x, l, k ? s : t]), q.fireWith(m, [x, y]), j && (n.trigger("ajaxComplete", [x, l]), --p.active || p.event.trigger("ajaxStop")))
                 }
                 "object" == typeof a && (c = a, a = b), c = c || {};
                 var d, e, f, g, h, i, j, k, l = p.ajaxSetup({}, c),
               m = l.context || l,
               n = m !== l && (m.nodeType || m instanceof p) ? p(m) : p.event,
               o = p.Deferred(),
               q = p.Callbacks("once memory"),
               r = l.statusCode || {},
               t = {},
               u = {},
               v = 0,
               w = "canceled",
               x = {
                 readyState: 0,
               setRequestHeader: function(a, b) {
                 if (!v) {
                   var c = a.toLowerCase();
                   a = u[c] = u[c] || a, t[a] = b
                 }
                 return this
               },
               getAllResponseHeaders: function() {
                 return 2 === v ? e : null
               },
               getResponseHeader: function(a) {
                 var c;
                 if (2 === v) {
                   if (!f)
                     for (f = {}; c = cm.exec(e);) f[c[1].toLowerCase()] = c[2];
               c = f[a.toLowerCase()]
                 }
                 return c === b ? null : c
               },
               overrideMimeType: function(a) {
                 return v || (l.mimeType = a), this
               },
               abort: function(a) {
                 return a = a || w, g && g.abort(a), y(0, a), this
               }
               };
               if (o.promise(x), x.success = x.done, x.error = x.fail, x.complete = q.add, x.statusCode = function(a) {
                 if (a) {
                   var b;
                   if (2 > v)
                     for (b in a) r[b] = [r[b], a[b]];
                   else b = a[x.status], x.always(b)
                 }
                 return this
               }, l.url = ((a || l.url) + "").replace(cl, "").replace(cp, cj[1] + "//"), l.dataTypes = p.trim(l.dataType || "*").toLowerCase().split(s), null == l.crossDomain && (i = ct.exec(l.url.toLowerCase()) || !1, l.crossDomain = i && i.join(":") + (i[3] ? "" : "http:" === i[1] ? 80 : 443) !== cj.join(":") + (cj[3] ? "" : "http:" === cj[1] ? 80 : 443)), l.data && l.processData && "string" != typeof l.data && (l.data = p.param(l.data, l.traditional)), cA(cv, l, c, x), 2 === v) return x;
               if (j = l.global, l.type = l.type.toUpperCase(), l.hasContent = !co.test(l.type), j && 0 === p.active++ && p.event.trigger("ajaxStart"), !l.hasContent && (l.data && (l.url += (cq.test(l.url) ? "&" : "?") + l.data, delete l.data), d = l.url, l.cache === !1)) {
                 var z = p.now(),
               A = l.url.replace(cs, "$1_=" + z);
               l.url = A + (A === l.url ? (cq.test(l.url) ? "&" : "?") + "_=" + z : "")
               }(l.data && l.hasContent && l.contentType !== !1 || c.contentType) && x.setRequestHeader("Content-Type", l.contentType), l.ifModified && (d = d || l.url, p.lastModified[d] && x.setRequestHeader("If-Modified-Since", p.lastModified[d]), p.etag[d] && x.setRequestHeader("If-None-Match", p.etag[d])), x.setRequestHeader("Accept", l.dataTypes[0] && l.accepts[l.dataTypes[0]] ? l.accepts[l.dataTypes[0]] + ("*" !== l.dataTypes[0] ? ", " + cx + "; q=0.01" : "") : l.accepts["*"]);
               for (k in l.headers) x.setRequestHeader(k, l.headers[k]);
               if (!l.beforeSend || l.beforeSend.call(m, x, l) !== !1 && 2 !== v) {
                 w = "abort";
                 for (k in {
                   success: 1,
                   error: 1,
                   complete: 1
                 }) x[k](l[k]);
                 if (g = cA(cw, l, c, x)) {
                   x.readyState = 1, j && n.trigger("ajaxSend", [x, l]), l.async && l.timeout > 0 && (h = setTimeout(function() {
                     x.abort("timeout")
                   }, l.timeout));
                   try {
                     v = 1, g.send(t, y)
                   } catch (B) {
                     if (!(2 > v)) throw B;
               y(-1, B)
                   }
                 } else y(-1, "No Transport");
               return x
               }
               return x.abort()
               },
               active: 0,
               lastModified: {},
               etag: {}
  });
  var cE = [],
  cF = /\?/,
  cG = /(=)\?(?=&|$)|\?\?/,
  cH = p.now();
  p.ajaxSetup({
    jsonp: "callback",
    jsonpCallback: function() {
      var a = cE.pop() || p.expando + "_" + cH++;
      return this[a] = !0, a
    }
  }), p.ajaxPrefilter("json jsonp", function(c, d, e) {
    var f, g, h, i = c.data,
    j = c.url,
    k = c.jsonp !== !1,
    l = k && cG.test(j),
                      m = k && !l && "string" == typeof i && !(c.contentType || "").indexOf("application/x-www-form-urlencoded") && cG.test(i);
                      return "jsonp" === c.dataTypes[0] || l || m ? (f = c.jsonpCallback = p.isFunction(c.jsonpCallback) ? c.jsonpCallback() : c.jsonpCallback, g = a[f], l ? c.url = j.replace(cG, "$1" + f) : m ? c.data = i.replace(cG, "$1" + f) : k && (c.url += (cF.test(j) ? "&" : "?") + c.jsonp + "=" + f), c.converters["script json"] = function() {
                        return h || p.error(f + " was not called"), h[0]
                      }, c.dataTypes[0] = "json", a[f] = function() {
                        h = arguments
                      }, e.always(function() {
                        a[f] = g, c[f] && (c.jsonpCallback = d.jsonpCallback, cE.push(f)), h && p.isFunction(g) && g(h[0]), h = g = b
                      }), "script") : void 0
  }), p.ajaxSetup({
    accepts: {
      script: "text/javascript, application/javascript, application/ecmascript, application/x-ecmascript"
    },
    contents: {
      script: /javascript|ecmascript/
    },
    converters: {
      "text script": function(a) {
        return p.globalEval(a), a
      }
    }
  }), p.ajaxPrefilter("script", function(a) {
    a.cache === b && (a.cache = !1), a.crossDomain && (a.type = "GET", a.global = !1)
  }), p.ajaxTransport("script", function(a) {
    if (a.crossDomain) {
      var c, d = e.head || e.getElementsByTagName("head")[0] || e.documentElement;
      return {
        send: function(f, g) {
          c = e.createElement("script"), c.async = "async", a.scriptCharset && (c.charset = a.scriptCharset), c.src = a.url, c.onload = c.onreadystatechange = function(a, e) {
            (e || !c.readyState || /loaded|complete/.test(c.readyState)) && (c.onload = c.onreadystatechange = null, d && c.parentNode && d.removeChild(c), c = b, e || g(200, "success"))
          }, d.insertBefore(c, d.firstChild)
        },
        abort: function() {
          c && c.onload(0, 1)
        }
      }
    }
  });
  var cI, cJ = a.ActiveXObject ? function() {
    for (var a in cI) cI[a](0, 1)
  } : !1,
  cK = 0;
  p.ajaxSettings.xhr = a.ActiveXObject ? function() {
    return !this.isLocal && cL() || cM()
  } : cL,
  function(a) {
    p.extend(p.support, {
      ajax: !!a,
      cors: !!a && "withCredentials" in a
    })
  }(p.ajaxSettings.xhr()), p.support.ajax && p.ajaxTransport(function(c) {
    if (!c.crossDomain || p.support.cors) {
      var d;
      return {
        send: function(e, f) {
          var g, h, i = c.xhr();
          if (c.username ? i.open(c.type, c.url, c.async, c.username, c.password) : i.open(c.type, c.url, c.async), c.xhrFields)
            for (h in c.xhrFields) i[h] = c.xhrFields[h];
                                                             c.mimeType && i.overrideMimeType && i.overrideMimeType(c.mimeType), !c.crossDomain && !e["X-Requested-With"] && (e["X-Requested-With"] = "XMLHttpRequest");
            try {
              for (h in e) i.setRequestHeader(h, e[h])
            } catch (j) {}
            i.send(c.hasContent && c.data || null), d = function(a, e) {
              var h, j, k, l, m;
              try {
                if (d && (e || 4 === i.readyState))
                  if (d = b, g && (i.onreadystatechange = p.noop, cJ && delete cI[g]), e) 4 !== i.readyState && i.abort();
                                                             else {
                                                               h = i.status, k = i.getAllResponseHeaders(), l = {}, m = i.responseXML, m && m.documentElement && (l.xml = m);
                                                               try {
                                                                 l.text = i.responseText
                                                               } catch (a) {}
                                                               try {
                                                                 j = i.statusText
                                                               } catch (n) {
                                                                 j = ""
                                                               }
                                                               h || !c.isLocal || c.crossDomain ? 1223 === h && (h = 204) : h = l.text ? 200 : 404
                                                             }
              } catch (o) {
                e || f(-1, o)
              }
              l && f(h, j, l, k)
            }, c.async ? 4 === i.readyState ? setTimeout(d, 0) : (g = ++cK, cJ && (cI || (cI = {}, p(a).unload(cJ)), cI[g] = d), i.onreadystatechange = d) : d()
        },
        abort: function() {
          d && d(0, 1)
        }
      }
    }
  });
  var cN, cO, cP = /^(?:toggle|show|hide)$/,
  cQ = new RegExp("^(?:([-+])=|)(" + q + ")([a-z%]*)$", "i"),
  cR = /queueHooks$/,
  cS = [cY],
  cT = {
    "*": [function(a, b) {
      var c, d, e = this.createTween(a, b),
      f = cQ.exec(b),
      g = e.cur(),
      h = +g || 0,
      i = 1,
      j = 20;
      if (f) {
        if (c = +f[2], d = f[3] || (p.cssNumber[a] ? "" : "px"), "px" !== d && h) {
          h = p.css(e.elem, a, !0) || c || 1;
          do i = i || ".5", h /= i, p.style(e.elem, a, h + d); while (i !== (i = e.cur() / g) && 1 !== i && --j)
        }
        e.unit = d, e.start = h, e.end = f[1] ? h + (f[1] + 1) * c : c
      }
      return e
    }]
  };
  p.Animation = p.extend(cW, {
    tweener: function(a, b) {
      p.isFunction(a) ? (b = a, a = ["*"]) : a = a.split(" ");
      for (var c, d = 0, e = a.length; e > d; d++) c = a[d], cT[c] = cT[c] || [], cT[c].unshift(b)
    },
    prefilter: function(a, b) {
      b ? cS.unshift(a) : cS.push(a)
    }
  }), p.Tween = cZ, cZ.prototype = {
    constructor: cZ,
    init: function(a, b, c, d, e, f) {
      this.elem = a, this.prop = c, this.easing = e || "swing", this.options = b, this.start = this.now = this.cur(), this.end = d, this.unit = f || (p.cssNumber[c] ? "" : "px")
    },
    cur: function() {
      var a = cZ.propHooks[this.prop];
      return a && a.get ? a.get(this) : cZ.propHooks._default.get(this)
    },
    run: function(a) {
      var b, c = cZ.propHooks[this.prop];
      return this.pos = b = this.options.duration ? p.easing[this.easing](a, this.options.duration * a, 0, 1, this.options.duration) : a, this.now = (this.end - this.start) * b + this.start, this.options.step && this.options.step.call(this.elem, this.now, this), c && c.set ? c.set(this) : cZ.propHooks._default.set(this), this
    }
  }, cZ.prototype.init.prototype = cZ.prototype, cZ.propHooks = {
    _default: {
      get: function(a) {
        var b;
        return null == a.elem[a.prop] || a.elem.style && null != a.elem.style[a.prop] ? (b = p.css(a.elem, a.prop, !1, ""), b && "auto" !== b ? b : 0) : a.elem[a.prop]
      },
      set: function(a) {
        p.fx.step[a.prop] ? p.fx.step[a.prop](a) : a.elem.style && (null != a.elem.style[p.cssProps[a.prop]] || p.cssHooks[a.prop]) ? p.style(a.elem, a.prop, a.now + a.unit) : a.elem[a.prop] = a.now
      }
    }
  }, cZ.propHooks.scrollTop = cZ.propHooks.scrollLeft = {
    set: function(a) {
      a.elem.nodeType && a.elem.parentNode && (a.elem[a.prop] = a.now)
    }
  }, p.each(["toggle", "show", "hide"], function(a, b) {
    var c = p.fn[b];
    p.fn[b] = function(d, e, f) {
      return null == d || "boolean" == typeof d || !a && p.isFunction(d) && p.isFunction(e) ? c.apply(this, arguments) : this.animate(c$(b, !0), d, e, f)
    }
  }), p.fn.extend({
    fadeTo: function(a, b, c, d) {
      return this.filter(bZ).css("opacity", 0).show().end().animate({
        opacity: b
      }, a, c, d)
    },
    animate: function(a, b, c, d) {
      var e = p.isEmptyObject(a),
                  f = p.speed(b, c, d),
                  g = function() {
                    var b = cW(this, p.extend({}, a), f);
                    e && b.stop(!0)
                  };
                  return e || f.queue === !1 ? this.each(g) : this.queue(f.queue, g)
    },
    stop: function(a, c, d) {
      var e = function(a) {
        var b = a.stop;
        delete a.stop, b(d)
      };
      return "string" != typeof a && (d = c, c = a, a = b), c && a !== !1 && this.queue(a || "fx", []), this.each(function() {
        var b = !0,
        c = null != a && a + "queueHooks",
        f = p.timers,
        g = p._data(this);
        if (c) g[c] && g[c].stop && e(g[c]);
                                                                                                                  else
                                                                                                                    for (c in g) g[c] && g[c].stop && cR.test(c) && e(g[c]);
                                                                                                                  for (c = f.length; c--;) f[c].elem === this && (null == a || f[c].queue === a) && (f[c].anim.stop(d), b = !1, f.splice(c, 1));
                                                                                                                  (b || !d) && p.dequeue(this, a)
      })
    }
  }), p.each({
    slideDown: c$("show"),
             slideUp: c$("hide"),
             slideToggle: c$("toggle"),
             fadeIn: {
               opacity: "show"
             },
             fadeOut: {
               opacity: "hide"
             },
             fadeToggle: {
               opacity: "toggle"
             }
  }, function(a, b) {
    p.fn[a] = function(a, c, d) {
      return this.animate(b, a, c, d)
    }
  }), p.speed = function(a, b, c) {
    var d = a && "object" == typeof a ? p.extend({}, a) : {
      complete: c || !c && b || p.isFunction(a) && a,
      duration: a,
      easing: c && b || b && !p.isFunction(b) && b
    };
    return d.duration = p.fx.off ? 0 : "number" == typeof d.duration ? d.duration : d.duration in p.fx.speeds ? p.fx.speeds[d.duration] : p.fx.speeds._default, (null == d.queue || d.queue === !0) && (d.queue = "fx"), d.old = d.complete, d.complete = function() {
      p.isFunction(d.old) && d.old.call(this), d.queue && p.dequeue(this, d.queue)
    }, d
  }, p.easing = {
    linear: function(a) {
      return a
    },
    swing: function(a) {
      return .5 - Math.cos(a * Math.PI) / 2
    }
  }, p.timers = [], p.fx = cZ.prototype.init, p.fx.tick = function() {
    for (var a, b = p.timers, c = 0; c < b.length; c++) a = b[c], !a() && b[c] === a && b.splice(c--, 1);
    b.length || p.fx.stop()
  }, p.fx.timer = function(a) {
    a() && p.timers.push(a) && !cO && (cO = setInterval(p.fx.tick, p.fx.interval))
  }, p.fx.interval = 13, p.fx.stop = function() {
    clearInterval(cO), cO = null
  }, p.fx.speeds = {
    slow: 600,
    fast: 200,
    _default: 400
  }, p.fx.step = {}, p.expr && p.expr.filters && (p.expr.filters.animated = function(a) {
    return p.grep(p.timers, function(b) {
      return a === b.elem
    }).length
  });
  var c_ = /^(?:body|html)$/i;
  p.fn.offset = function(a) {
    if (arguments.length) return a === b ? this : this.each(function(b) {
      p.offset.setOffset(this, a, b)
    });
    var c, d, e, f, g, h, i, j = {
      top: 0,
      left: 0
    },
    k = this[0],
    l = k && k.ownerDocument;
    if (l) return (d = l.body) === k ? p.offset.bodyOffset(k) : (c = l.documentElement, p.contains(c, k) ? ("undefined" != typeof k.getBoundingClientRect && (j = k.getBoundingClientRect()), e = da(l), f = c.clientTop || d.clientTop || 0, g = c.clientLeft || d.clientLeft || 0, h = e.pageYOffset || c.scrollTop, i = e.pageXOffset || c.scrollLeft, {
      top: j.top + h - f,
      left: j.left + i - g
    }) : j)
  }, p.offset = {
    bodyOffset: function(a) {
      var b = a.offsetTop,
      c = a.offsetLeft;
      return p.support.doesNotIncludeMarginInBodyOffset && (b += parseFloat(p.css(a, "marginTop")) || 0, c += parseFloat(p.css(a, "marginLeft")) || 0), {
        top: b,
        left: c
      }
    },
    setOffset: function(a, b, c) {
      var d = p.css(a, "position");
      "static" === d && (a.style.position = "relative");
      var l, m, e = p(a),
      f = e.offset(),
      g = p.css(a, "top"),
      h = p.css(a, "left"),
      i = ("absolute" === d || "fixed" === d) && p.inArray("auto", [g, h]) > -1,
      j = {},
      k = {};
      i ? (k = e.position(), l = k.top, m = k.left) : (l = parseFloat(g) || 0, m = parseFloat(h) || 0), p.isFunction(b) && (b = b.call(a, c, f)), null != b.top && (j.top = b.top - f.top + l), null != b.left && (j.left = b.left - f.left + m), "using" in b ? b.using.call(a, j) : e.css(j)
    }
  }, p.fn.extend({
    position: function() {
      if (this[0]) {
        var a = this[0],
        b = this.offsetParent(),
                 c = this.offset(),
                 d = c_.test(b[0].nodeName) ? {
                   top: 0,
                 left: 0
                 } : b.offset();
                 return c.top -= parseFloat(p.css(a, "marginTop")) || 0, c.left -= parseFloat(p.css(a, "marginLeft")) || 0, d.top += parseFloat(p.css(b[0], "borderTopWidth")) || 0, d.left += parseFloat(p.css(b[0], "borderLeftWidth")) || 0, {
                   top: c.top - d.top,
                 left: c.left - d.left
                 }
      }
    },
    offsetParent: function() {
      return this.map(function() {
        for (var a = this.offsetParent || e.body; a && !c_.test(a.nodeName) && "static" === p.css(a, "position");) a = a.offsetParent;
                      return a || e.body
      })
    }
  }), p.each({
    scrollLeft: "pageXOffset",
    scrollTop: "pageYOffset"
  }, function(a, c) {
    var d = /Y/.test(c);
    p.fn[a] = function(e) {
      return p.access(this, function(a, e, f) {
        var g = da(a);
        return f === b ? g ? c in g ? g[c] : g.document.documentElement[e] : a[e] : void(g ? g.scrollTo(d ? p(g).scrollLeft() : f, d ? f : p(g).scrollTop()) : a[e] = f)
      }, a, e, arguments.length, null)
    }
  }), p.each({
    Height: "height",
    Width: "width"
  }, function(a, c) {
    p.each({
      padding: "inner" + a,
      content: c,
      "": "outer" + a
    }, function(d, e) {
      p.fn[e] = function(e, f) {
        var g = arguments.length && (d || "boolean" != typeof e),
           h = d || (e === !0 || f === !0 ? "margin" : "border");
           return p.access(this, function(c, d, e) {
             var f;
             return p.isWindow(c) ? c.document.documentElement["client" + a] : 9 === c.nodeType ? (f = c.documentElement, Math.max(c.body["scroll" + a], f["scroll" + a], c.body["offset" + a], f["offset" + a], f["client" + a])) : e === b ? p.css(c, d, e, h) : p.style(c, d, e, h)
           }, c, g ? e : b, g, null)
      }
    })
  }), a.jQuery = a.$ = p, "function" == typeof define && define.amd && define.amd.jQuery && define("jquery", [], function() {
    return p
  })
}(window),
function($, e, b) {
  function a(j) {
    return j = j || location.href, "#" + j.replace(/^[^#]*#?(.*)$/, "$1")
  }
  var f, c = "hashchange",
  h = document,
  g = $.event.special,
  i = h.documentMode,
  d = "on" + c in e && (i === b || i > 7);
  $.fn[c] = function(j) {
    return j ? this.bind(c, j) : this.trigger(c)
  }, $.fn[c].delay = 50, g[c] = $.extend(g[c], {
    setup: function() {
      return d ? !1 : void $(f.start)
    },
    teardown: function() {
      return d ? !1 : void $(f.stop)
    }
  }), f = function() {
    function n() {
      var r = a(),
      q = o(m);
      r !== m ? (l(m = r, q), $(e).trigger(c)) : q !== m && (location.href = location.href.replace(/#.*/, "") + q), p = setTimeout(n, $.fn[c].delay)
    }
    var p, j = {},
    m = a(),
    k = function(q) {
      return q
    },
    l = k,
    o = k;
    return j.start = function() {
      p || n()
    }, j.stop = function() {
      p && clearTimeout(p), p = b
    }, $.browser.msie && !d && function() {
      var q, r;
      j.start = function() {
        q || (r = $.fn[c].src, r = r && r + a(), q = $('<iframe tabindex="-1" title="empty"/>').hide().one("load", function() {
          r || l(a()), n()
        }).attr("src", r || "javascript:0").insertAfter("body")[0].contentWindow, h.onpropertychange = function() {
          try {
            "title" === event.propertyName && (q.document.title = h.title)
          } catch (s) {}
        })
      }, j.stop = k, o = function() {
        return a(q.location.href)
      }, l = function(v, s) {
        var u = q.document,
        t = $.fn[c].domain;
        v !== s && (u.title = h.title, u.open(), t && u.write('<script>document.domain="' + t + '"</script>'), u.close(), q.location.hash = v)
      }
    }(), j
  }()
}(jQuery, this),
function($) {
  function now() {
    return (new Date).getTime()
  }
  var encode = encodeURIComponent,
  decode = decodeURIComponent;
  $.cookie = function(key, value, options) {
    options = $.extend({}, options);
    var expires = options.expires,
    result = value;
    return key ? (key = encode(key), void 0 === value ? (result = new RegExp("(?:^|; )" + key + "=([^;]*)").exec(document.cookie), result && JSON.parse(decode(result[1]))) : (null === value && (expires = -1), "number" == typeof expires && (expires = new Date(now() + expires)), document.cookie = [key, "=", encode(JSON.stringify(value)), expires ? "; expires=" + expires.toUTCString() : "", options.path ? "; path=" + options.path : "", options.domain ? "; domain=" + options.domain : "", options.secure ? "; secure" : ""].join(""), result)) : (result = {}, $.each(document.cookie.split("; "), function(i, cookie) {
      if (cookie) {
        var parts = cookie.split("=");
        result[decode(parts[0])] = JSON.parse(decode(parts[1]))
      }
    }), result)
  }, $.support && ! function() {
    var test = "jsoncookie" + now();
    $.cookie(test, test), $.support.cookie = $.cookie(test) === test, $.cookie(test, null)
  }()
}(jQuery),
function() {
  var n = this,
  t = n._,
  r = {},
  e = Array.prototype,
  u = Object.prototype,
  i = Function.prototype,
  a = e.push,
  o = e.slice,
  c = e.concat,
  l = u.toString,
  f = u.hasOwnProperty,
  s = e.forEach,
  p = e.map,
  h = e.reduce,
  v = e.reduceRight,
  g = e.filter,
  d = e.every,
  m = e.some,
  y = e.indexOf,
  b = e.lastIndexOf,
  x = Array.isArray,
  w = Object.keys,
  _ = i.bind,
  j = function(n) {
    return n instanceof j ? n : this instanceof j ? void(this._wrapped = n) : new j(n)
  };
  "undefined" != typeof exports ? ("undefined" != typeof module && module.exports && (exports = module.exports = j), exports._ = j) : n._ = j, j.VERSION = "1.5.2";
  var A = j.each = j.forEach = function(n, t, e) {
    if (null != n)
      if (s && n.forEach === s) n.forEach(t, e);
      else if (n.length === +n.length) {
        for (var u = 0, i = n.length; i > u; u++)
          if (t.call(e, n[u], u, n) === r) return
      } else
        for (var a = j.keys(n), u = 0, i = a.length; i > u; u++)
          if (t.call(e, n[a[u]], a[u], n) === r) return
  };
  j.map = j.collect = function(n, t, r) {
    var e = [];
    return null == n ? e : p && n.map === p ? n.map(t, r) : (A(n, function(n, u, i) {
      e.push(t.call(r, n, u, i))
    }), e)
  };
  var E = "Reduce of empty array with no initial value";
  j.reduce = j.foldl = j.inject = function(n, t, r, e) {
    var u = arguments.length > 2;
    if (null == n && (n = []), h && n.reduce === h) return e && (t = j.bind(t, e)), u ? n.reduce(t, r) : n.reduce(t);
    if (A(n, function(n, i, a) {
      u ? r = t.call(e, r, n, i, a) : (r = n, u = !0)
    }), !u) throw new TypeError(E);
    return r
  }, j.reduceRight = j.foldr = function(n, t, r, e) {
    var u = arguments.length > 2;
    if (null == n && (n = []), v && n.reduceRight === v) return e && (t = j.bind(t, e)), u ? n.reduceRight(t, r) : n.reduceRight(t);
    var i = n.length;
    if (i !== +i) {
      var a = j.keys(n);
      i = a.length
    }
    if (A(n, function(o, c, l) {
      c = a ? a[--i] : --i, u ? r = t.call(e, r, n[c], c, l) : (r = n[c], u = !0)
    }), !u) throw new TypeError(E);
    return r
  }, j.find = j.detect = function(n, t, r) {
    var e;
    return O(n, function(n, u, i) {
      return t.call(r, n, u, i) ? (e = n, !0) : void 0
    }), e
  }, j.filter = j.select = function(n, t, r) {
    var e = [];
    return null == n ? e : g && n.filter === g ? n.filter(t, r) : (A(n, function(n, u, i) {
      t.call(r, n, u, i) && e.push(n)
    }), e)
  }, j.reject = function(n, t, r) {
    return j.filter(n, function(n, e, u) {
      return !t.call(r, n, e, u)
    }, r)
  }, j.every = j.all = function(n, t, e) {
    t || (t = j.identity);
    var u = !0;
    return null == n ? u : d && n.every === d ? n.every(t, e) : (A(n, function(n, i, a) {
      return (u = u && t.call(e, n, i, a)) ? void 0 : r
    }), !!u)
  };
  var O = j.some = j.any = function(n, t, e) {
    t || (t = j.identity);
    var u = !1;
    return null == n ? u : m && n.some === m ? n.some(t, e) : (A(n, function(n, i, a) {
      return u || (u = t.call(e, n, i, a)) ? r : void 0
    }), !!u)
  };
  j.contains = j.include = function(n, t) {
    return null == n ? !1 : y && n.indexOf === y ? -1 != n.indexOf(t) : O(n, function(n) {
      return n === t
    })
  }, j.invoke = function(n, t) {
    var r = o.call(arguments, 2),
    e = j.isFunction(t);
    return j.map(n, function(n) {
      return (e ? t : n[t]).apply(n, r)
    })
  }, j.pluck = function(n, t) {
    return j.map(n, function(n) {
      return n[t]
    })
  }, j.where = function(n, t, r) {
    return j.isEmpty(t) ? r ? void 0 : [] : j[r ? "find" : "filter"](n, function(n) {
      for (var r in t)
        if (t[r] !== n[r]) return !1;
                                                                     return !0
    })
  }, j.findWhere = function(n, t) {
    return j.where(n, t, !0)
  }, j.max = function(n, t, r) {
    if (!t && j.isArray(n) && n[0] === +n[0] && n.length < 65535) return Math.max.apply(Math, n);
    if (!t && j.isEmpty(n)) return -1 / 0;
    var e = {
      computed: -1 / 0,
      value: -1 / 0
    };
    return A(n, function(n, u, i) {
      var a = t ? t.call(r, n, u, i) : n;
      a > e.computed && (e = {
        value: n,
        computed: a
      })
    }), e.value
  }, j.min = function(n, t, r) {
    if (!t && j.isArray(n) && n[0] === +n[0] && n.length < 65535) return Math.min.apply(Math, n);
    if (!t && j.isEmpty(n)) return 1 / 0;
    var e = {
      computed: 1 / 0,
      value: 1 / 0
    };
    return A(n, function(n, u, i) {
      var a = t ? t.call(r, n, u, i) : n;
      a < e.computed && (e = {
        value: n,
        computed: a
      })
    }), e.value
  }, j.shuffle = function(n) {
    var t, r = 0,
    e = [];
    return A(n, function(n) {
      t = j.random(r++), e[r - 1] = e[t], e[t] = n
    }), e
  }, j.sample = function(n, t, r) {
    return arguments.length < 2 || r ? n[j.random(n.length - 1)] : j.shuffle(n).slice(0, Math.max(0, t))
  };
  var k = function(n) {
    return j.isFunction(n) ? n : function(t) {
      return t[n]
    }
  };
  j.sortBy = function(n, t, r) {
    var e = k(t);
    return j.pluck(j.map(n, function(n, t, u) {
      return {
        value: n,
        index: t,
        criteria: e.call(r, n, t, u)
      }
    }).sort(function(n, t) {
      var r = n.criteria,
      e = t.criteria;
      if (r !== e) {
        if (r > e || void 0 === r) return 1;
            if (e > r || void 0 === e) return -1
      }
      return n.index - t.index
    }), "value")
  };
  var F = function(n) {
    return function(t, r, e) {
      var u = {},
      i = null == r ? j.identity : k(r);
      return A(t, function(r, a) {
        var o = i.call(e, r, a, t);
        n(u, o, r)
      }), u
    }
  };
  j.groupBy = F(function(n, t, r) {
    (j.has(n, t) ? n[t] : n[t] = []).push(r)
  }), j.indexBy = F(function(n, t, r) {
    n[t] = r
  }), j.countBy = F(function(n, t) {
    j.has(n, t) ? n[t] ++ : n[t] = 1
  }), j.sortedIndex = function(n, t, r, e) {
    r = null == r ? j.identity : k(r);
    for (var u = r.call(e, t), i = 0, a = n.length; a > i;) {
      var o = i + a >>> 1;
      r.call(e, n[o]) < u ? i = o + 1 : a = o
    }
    return i
  }, j.toArray = function(n) {
    return n ? j.isArray(n) ? o.call(n) : n.length === +n.length ? j.map(n, j.identity) : j.values(n) : []
  }, j.size = function(n) {
    return null == n ? 0 : n.length === +n.length ? n.length : j.keys(n).length
  }, j.first = j.head = j.take = function(n, t, r) {
    return null == n ? void 0 : null == t || r ? n[0] : o.call(n, 0, t)
  }, j.initial = function(n, t, r) {
    return o.call(n, 0, n.length - (null == t || r ? 1 : t))
  }, j.last = function(n, t, r) {
    return null == n ? void 0 : null == t || r ? n[n.length - 1] : o.call(n, Math.max(n.length - t, 0))
  }, j.rest = j.tail = j.drop = function(n, t, r) {
    return o.call(n, null == t || r ? 1 : t)
  }, j.compact = function(n) {
    return j.filter(n, j.identity)
  };
  var M = function(n, t, r) {
    return t && j.every(n, j.isArray) ? c.apply(r, n) : (A(n, function(n) {
      j.isArray(n) || j.isArguments(n) ? t ? a.apply(r, n) : M(n, t, r) : r.push(n)
    }), r)
  };
  j.flatten = function(n, t) {
    return M(n, t, [])
  }, j.without = function(n) {
    return j.difference(n, o.call(arguments, 1))
  }, j.uniq = j.unique = function(n, t, r, e) {
    j.isFunction(t) && (e = r, r = t, t = !1);
    var u = r ? j.map(n, r, e) : n,
    i = [],
    a = [];
    return A(u, function(r, e) {
      (t ? e && a[a.length - 1] === r : j.contains(a, r)) || (a.push(r), i.push(n[e]))
    }), i
  }, j.union = function() {
    return j.uniq(j.flatten(arguments, !0))
  }, j.intersection = function(n) {
    var t = o.call(arguments, 1);
    return j.filter(j.uniq(n), function(n) {
      return j.every(t, function(t) {
        return j.indexOf(t, n) >= 0
      })
    })
  }, j.difference = function(n) {
    var t = c.apply(e, o.call(arguments, 1));
    return j.filter(n, function(n) {
      return !j.contains(t, n)
    })
  }, j.zip = function() {
    for (var n = j.max(j.pluck(arguments, "length").concat(0)), t = new Array(n), r = 0; n > r; r++) t[r] = j.pluck(arguments, "" + r);
    return t
  }, j.object = function(n, t) {
    if (null == n) return {};
    for (var r = {}, e = 0, u = n.length; u > e; e++) t ? r[n[e]] = t[e] : r[n[e][0]] = n[e][1];
    return r
  }, j.indexOf = function(n, t, r) {
    if (null == n) return -1;
    var e = 0,
    u = n.length;
    if (r) {
      if ("number" != typeof r) return e = j.sortedIndex(n, t), n[e] === t ? e : -1;
      e = 0 > r ? Math.max(0, u + r) : r
    }
    if (y && n.indexOf === y) return n.indexOf(t, r);
    for (; u > e; e++)
      if (n[e] === t) return e;
      return -1
  }, j.lastIndexOf = function(n, t, r) {
    if (null == n) return -1;
    var e = null != r;
    if (b && n.lastIndexOf === b) return e ? n.lastIndexOf(t, r) : n.lastIndexOf(t);
    for (var u = e ? r : n.length; u--;)
      if (n[u] === t) return u;
      return -1
  }, j.range = function(n, t, r) {
    arguments.length <= 1 && (t = n || 0, n = 0), r = arguments[2] || 1;
    for (var e = Math.max(Math.ceil((t - n) / r), 0), u = 0, i = new Array(e); e > u;) i[u++] = n, n += r;
    return i
  };
  var R = function() {};
  j.bind = function(n, t) {
    var r, e;
    if (_ && n.bind === _) return _.apply(n, o.call(arguments, 1));
    if (!j.isFunction(n)) throw new TypeError;
    return r = o.call(arguments, 2), e = function() {
      if (!(this instanceof e)) return n.apply(t, r.concat(o.call(arguments)));
      R.prototype = n.prototype;
      var u = new R;
      R.prototype = null;
      var i = n.apply(u, r.concat(o.call(arguments)));
      return Object(i) === i ? i : u
    }
  }, j.partial = function(n) {
    var t = o.call(arguments, 1);
    return function() {
      return n.apply(this, t.concat(o.call(arguments)))
    }
  }, j.bindAll = function(n) {
    var t = o.call(arguments, 1);
    if (0 === t.length) throw new Error("bindAll must be passed function names");
    return A(t, function(t) {
      n[t] = j.bind(n[t], n)
    }), n
  }, j.memoize = function(n, t) {
    var r = {};
    return t || (t = j.identity),
    function() {
      var e = t.apply(this, arguments);
      return j.has(r, e) ? r[e] : r[e] = n.apply(this, arguments)
    }
  }, j.delay = function(n, t) {
    var r = o.call(arguments, 2);
    return setTimeout(function() {
      return n.apply(null, r)
    }, t)
  }, j.defer = function(n) {
    return j.delay.apply(j, [n, 1].concat(o.call(arguments, 1)))
  }, j.throttle = function(n, t, r) {
    var e, u, i, a = null,
    o = 0;
    r || (r = {});
    var c = function() {
      o = r.leading === !1 ? 0 : new Date, a = null, i = n.apply(e, u)
    };
    return function() {
      var l = new Date;
      o || r.leading !== !1 || (o = l);
      var f = t - (l - o);
      return e = this, u = arguments, 0 >= f ? (clearTimeout(a), a = null, o = l, i = n.apply(e, u)) : a || r.trailing === !1 || (a = setTimeout(c, f)), i
    }
  }, j.debounce = function(n, t, r) {
    var e, u, i, a, o;
    return function() {
      i = this, u = arguments, a = new Date;
      var c = function() {
        var l = new Date - a;
        t > l ? e = setTimeout(c, t - l) : (e = null, r || (o = n.apply(i, u)))
      },
      l = r && !e;
      return e || (e = setTimeout(c, t)), l && (o = n.apply(i, u)), o
    }
  }, j.once = function(n) {
    var t, r = !1;
    return function() {
      return r ? t : (r = !0, t = n.apply(this, arguments), n = null, t)
    }
  }, j.wrap = function(n, t) {
    return function() {
      var r = [n];
      return a.apply(r, arguments), t.apply(this, r)
    }
  }, j.compose = function() {
    var n = arguments;
    return function() {
      for (var t = arguments, r = n.length - 1; r >= 0; r--) t = [n[r].apply(this, t)];
      return t[0]
    }
  }, j.after = function(n, t) {
    return function() {
      return --n < 1 ? t.apply(this, arguments) : void 0
    }
  }, j.keys = w || function(n) {
    if (n !== Object(n)) throw new TypeError("Invalid object");
    var t = [];
    for (var r in n) j.has(n, r) && t.push(r);
    return t
  }, j.values = function(n) {
    for (var t = j.keys(n), r = t.length, e = new Array(r), u = 0; r > u; u++) e[u] = n[t[u]];
    return e
  }, j.pairs = function(n) {
    for (var t = j.keys(n), r = t.length, e = new Array(r), u = 0; r > u; u++) e[u] = [t[u], n[t[u]]];
    return e
  }, j.invert = function(n) {
    for (var t = {}, r = j.keys(n), e = 0, u = r.length; u > e; e++) t[n[r[e]]] = r[e];
    return t
  }, j.functions = j.methods = function(n) {
    var t = [];
    for (var r in n) j.isFunction(n[r]) && t.push(r);
    return t.sort()
  }, j.extend = function(n) {
    return A(o.call(arguments, 1), function(t) {
      if (t)
        for (var r in t) n[r] = t[r]
    }), n
  }, j.pick = function(n) {
    var t = {},
    r = c.apply(e, o.call(arguments, 1));
    return A(r, function(r) {
      r in n && (t[r] = n[r])
    }), t
  }, j.omit = function(n) {
    var t = {},
    r = c.apply(e, o.call(arguments, 1));
    for (var u in n) j.contains(r, u) || (t[u] = n[u]);
    return t
  }, j.defaults = function(n) {
    return A(o.call(arguments, 1), function(t) {
      if (t)
        for (var r in t) void 0 === n[r] && (n[r] = t[r])
    }), n
  }, j.clone = function(n) {
    return j.isObject(n) ? j.isArray(n) ? n.slice() : j.extend({}, n) : n
  }, j.tap = function(n, t) {
    return t(n), n
  };
  var S = function(n, t, r, e) {
    if (n === t) return 0 !== n || 1 / n == 1 / t;
    if (null == n || null == t) return n === t;
    n instanceof j && (n = n._wrapped), t instanceof j && (t = t._wrapped);
    var u = l.call(n);
    if (u != l.call(t)) return !1;
    switch (u) {
      case "[object String]":
        return n == String(t);
      case "[object Number]":
        return n != +n ? t != +t : 0 == n ? 1 / n == 1 / t : n == +t;
      case "[object Date]":
      case "[object Boolean]":
        return +n == +t;
      case "[object RegExp]":
        return n.source == t.source && n.global == t.global && n.multiline == t.multiline && n.ignoreCase == t.ignoreCase
    }
    if ("object" != typeof n || "object" != typeof t) return !1;
    for (var i = r.length; i--;)
      if (r[i] == n) return e[i] == t;
      var a = n.constructor,
      o = t.constructor;
    if (a !== o && !(j.isFunction(a) && a instanceof a && j.isFunction(o) && o instanceof o)) return !1;
    r.push(n), e.push(t);
    var c = 0,
    f = !0;
    if ("[object Array]" == u) {
      if (c = n.length, f = c == t.length)
        for (; c-- && (f = S(n[c], t[c], r, e)););
    } else {
      for (var s in n)
        if (j.has(n, s) && (c++, !(f = j.has(t, s) && S(n[s], t[s], r, e)))) break;
        if (f) {
          for (s in t)
            if (j.has(t, s) && !c--) break;
            f = !c
        }
    }
    return r.pop(), e.pop(), f
  };
  j.isEqual = function(n, t) {
    return S(n, t, [], [])
  }, j.isEmpty = function(n) {
    if (null == n) return !0;
    if (j.isArray(n) || j.isString(n)) return 0 === n.length;
    for (var t in n)
      if (j.has(n, t)) return !1;
      return !0
  }, j.isElement = function(n) {
    return !(!n || 1 !== n.nodeType)
  }, j.isArray = x || function(n) {
    return "[object Array]" == l.call(n)
  }, j.isObject = function(n) {
    return n === Object(n)
  }, A(["Arguments", "Function", "String", "Number", "Date", "RegExp"], function(n) {
    j["is" + n] = function(t) {
      return l.call(t) == "[object " + n + "]"
    }
  }), j.isArguments(arguments) || (j.isArguments = function(n) {
    return !(!n || !j.has(n, "callee"))
  }), "function" != typeof /./ && (j.isFunction = function(n) {
    return "function" == typeof n
  }), j.isFinite = function(n) {
    return isFinite(n) && !isNaN(parseFloat(n))
  }, j.isNaN = function(n) {
    return j.isNumber(n) && n != +n
  }, j.isBoolean = function(n) {
    return n === !0 || n === !1 || "[object Boolean]" == l.call(n)
  }, j.isNull = function(n) {
    return null === n
  }, j.isUndefined = function(n) {
    return void 0 === n
  }, j.has = function(n, t) {
    return f.call(n, t)
  }, j.noConflict = function() {
    return n._ = t, this
  }, j.identity = function(n) {
    return n
  }, j.times = function(n, t, r) {
    for (var e = Array(Math.max(0, n)), u = 0; n > u; u++) e[u] = t.call(r, u);
    return e
  }, j.random = function(n, t) {
    return null == t && (t = n, n = 0), n + Math.floor(Math.random() * (t - n + 1))
  };
  var I = {
    escape: {
      "&": "&amp;",
      "<": "&lt;",
      ">": "&gt;",
      '"': "&quot;",
      "'": "&#x27;"
    }
  };
  I.unescape = j.invert(I.escape);
  var T = {
    escape: new RegExp("[" + j.keys(I.escape).join("") + "]", "g"),
    unescape: new RegExp("(" + j.keys(I.unescape).join("|") + ")", "g")
  };
  j.each(["escape", "unescape"], function(n) {
    j[n] = function(t) {
      return null == t ? "" : ("" + t).replace(T[n], function(t) {
        return I[n][t]
      })
    }
  }), j.result = function(n, t) {
    if (null == n) return void 0;
    var r = n[t];
    return j.isFunction(r) ? r.call(n) : r
  }, j.mixin = function(n) {
    A(j.functions(n), function(t) {
      var r = j[t] = n[t];
      j.prototype[t] = function() {
        var n = [this._wrapped];
        return a.apply(n, arguments), z.call(this, r.apply(j, n))
      }
    })
  };
  var N = 0;
  j.uniqueId = function(n) {
    var t = ++N + "";
    return n ? n + t : t
  }, j.templateSettings = {
    evaluate: /<%([\s\S]+?)%>/g,
    interpolate: /<%=([\s\S]+?)%>/g,
    escape: /<%-([\s\S]+?)%>/g
  };
  var q = /(.)^/,
  B = {
    "'": "'",
    "\\": "\\",
    "\r": "r",
    "\n": "n",
    " ": "t",
    "\u2028": "u2028",
    "\u2029": "u2029"
  },
  D = /\\|'|\r|\n|\t|\u2028|\u2029/g;
  j.template = function(n, t, r) {
    var e;
    r = j.defaults({}, r, j.templateSettings);
    var u = new RegExp([(r.escape || q).source, (r.interpolate || q).source, (r.evaluate || q).source].join("|") + "|$", "g"),
    i = 0,
    a = "__p+='";
    n.replace(u, function(t, r, e, u, o) {
      return a += n.slice(i, o).replace(D, function(n) {
        return "\\" + B[n]
      }), r && (a += "'+\n((__t=(" + r + "))==null?'':_.escape(__t))+\n'"), e && (a += "'+\n((__t=(" + e + "))==null?'':__t)+\n'"), u && (a += "';\n" + u + "\n__p+='"), i = o + t.length, t
    }), a += "';\n", r.variable || (a = "with(obj||{}){\n" + a + "}\n"), a = "var __t,__p='',__j=Array.prototype.join,print=function(){__p+=__j.call(arguments,'');};\n" + a + "return __p;\n";
    try {
      e = new Function(r.variable || "obj", "_", a)
    } catch (o) {
      throw o.source = a, o
    }
    if (t) return e(t, j);
    var c = function(n) {
      return e.call(this, n, j)
    };
    return c.source = "function(" + (r.variable || "obj") + "){\n" + a + "}", c
  }, j.chain = function(n) {
    return j(n).chain()
  };
  var z = function(n) {
    return this._chain ? j(n).chain() : n
  };
  j.mixin(j), A(["pop", "push", "reverse", "shift", "sort", "splice", "unshift"], function(n) {
    var t = e[n];
    j.prototype[n] = function() {
      var r = this._wrapped;
      return t.apply(r, arguments), "shift" != n && "splice" != n || 0 !== r.length || delete r[0], z.call(this, r)
    }
  }), A(["concat", "join", "slice"], function(n) {
    var t = e[n];
    j.prototype[n] = function() {
      return z.call(this, t.apply(this._wrapped, arguments))
    }
  }), j.extend(j.prototype, {
    chain: function() {
      return this._chain = !0, this
    },
    value: function() {
      return this._wrapped
    }
  })
}.call(this), FastClick.prototype.deviceIsAndroid = navigator.userAgent.indexOf("Android") > 0, FastClick.prototype.deviceIsIOS = /iP(ad|hone|od)/.test(navigator.userAgent), FastClick.prototype.deviceIsIOS4 = FastClick.prototype.deviceIsIOS && /OS 4_\d(_\d)?/.test(navigator.userAgent), FastClick.prototype.deviceIsIOSWithBadTarget = FastClick.prototype.deviceIsIOS && /OS ([6-9]|\d{2})_\d/.test(navigator.userAgent), FastClick.prototype.needsClick = function(a) {
  "use strict";
  switch (a.nodeName.toLowerCase()) {
    case "button":
    case "select":
    case "textarea":
      if (a.disabled) return !0;
      break;
    case "input":
      if (this.deviceIsIOS && "file" === a.type || a.disabled) return !0;
      break;
    case "label":
    case "video":
      return !0
  }
  return /\bneedsclick\b/.test(a.className)
}, FastClick.prototype.needsFocus = function(a) {
  "use strict";
    switch (a.nodeName.toLowerCase()) {
      case "textarea":
      case "select":
        return !0;
      case "input":
        switch (a.type) {
          case "button":
          case "checkbox":
          case "file":
          case "image":
          case "radio":
          case "submit":
            return !1
        }
        return !a.disabled && !a.readOnly;
          default:
            return /\bneedsfocus\b/.test(a.className)
    }
}, FastClick.prototype.sendClick = function(a, b) {
  "use strict";
      var c, d;
      document.activeElement && document.activeElement !== a && document.activeElement.blur(), d = b.changedTouches[0], c = document.createEvent("MouseEvents"), c.initMouseEvent("click", !0, !0, window, 1, d.screenX, d.screenY, d.clientX, d.clientY, !1, !1, !1, !1, 0, null), c.forwardedTouchEvent = !0, a.dispatchEvent(c)
}, FastClick.prototype.focus = function(a) {
  "use strict";
      var b;
      this.deviceIsIOS && a.setSelectionRange ? (b = a.value.length, a.setSelectionRange(b, b)) : a.focus()
}, FastClick.prototype.updateScrollParent = function(a) {
  "use strict";
      var b, c;
      if (b = a.fastClickScrollParent, !b || !b.contains(a)) {
        c = a;
        do {
          if (c.scrollHeight > c.offsetHeight) {
            b = c, a.fastClickScrollParent = c;
            break
          }
          c = c.parentElement
        } while (c)
      }
      b && (b.fastClickLastScrollTop = b.scrollTop)
}, FastClick.prototype.getTargetElementFromEventTarget = function(a) {
  "use strict";
      return a.nodeType === Node.TEXT_NODE ? a.parentNode : a
}, FastClick.prototype.onTouchStart = function(a) {
  "use strict";
      var b, c, d;
      if (a.targetTouches.length > 1) return !0;
      if (b = this.getTargetElementFromEventTarget(a.target), c = a.targetTouches[0], this.deviceIsIOS) {
        if (d = window.getSelection(), d.rangeCount && !d.isCollapsed) return !0;
        if (!this.deviceIsIOS4) {
          if (c.identifier === this.lastTouchIdentifier) return a.preventDefault(), !1;
          this.lastTouchIdentifier = c.identifier, this.updateScrollParent(b)
        }
      }
      return this.trackingClick = !0, this.trackingClickStart = a.timeStamp, this.targetElement = b, this.touchStartX = c.pageX, this.touchStartY = c.pageY, a.timeStamp - this.lastClickTime < 200 && a.preventDefault(), !0
}, FastClick.prototype.touchHasMoved = function(a) {
  "use strict";
      var b = a.changedTouches[0],
      c = this.touchBoundary;
      return Math.abs(b.pageX - this.touchStartX) > c || Math.abs(b.pageY - this.touchStartY) > c ? !0 : !1
}, FastClick.prototype.onTouchMove = function(a) {
  "use strict";
      return this.trackingClick ? ((this.targetElement !== this.getTargetElementFromEventTarget(a.target) || this.touchHasMoved(a)) && (this.trackingClick = !1, this.targetElement = null), !0) : !0
}, FastClick.prototype.findControl = function(a) {
  "use strict";
      return void 0 !== a.control ? a.control : a.htmlFor ? document.getElementById(a.htmlFor) : a.querySelector("button, input:not([type=hidden]), keygen, meter, output, progress, select, textarea")
}, FastClick.prototype.onTouchEnd = function(a) {
  "use strict";
      var b, c, d, e, f, g = this.targetElement;
      if (!this.trackingClick) return !0;
      if (a.timeStamp - this.lastClickTime < 200) return this.cancelNextClick = !0, !0;
      if (this.lastClickTime = a.timeStamp, c = this.trackingClickStart, this.trackingClick = !1, this.trackingClickStart = 0, this.deviceIsIOSWithBadTarget && (f = a.changedTouches[0], g = document.elementFromPoint(f.pageX - window.pageXOffset, f.pageY - window.pageYOffset) || g, g.fastClickScrollParent = this.targetElement.fastClickScrollParent), d = g.tagName.toLowerCase(), "label" === d) {
        if (b = this.findControl(g)) {
          if (this.focus(g), this.deviceIsAndroid) return !1;
          g = b
        }
      } else if (this.needsFocus(g)) return a.timeStamp - c > 100 || this.deviceIsIOS && window.top !== window && "input" === d ? (this.targetElement = null, !1) : (this.focus(g), this.deviceIsIOS4 && "select" === d || (this.targetElement = null, a.preventDefault()), !1);
      return this.deviceIsIOS && !this.deviceIsIOS4 && (e = g.fastClickScrollParent, e && e.fastClickLastScrollTop !== e.scrollTop) ? !0 : (this.needsClick(g) || (a.preventDefault(), this.sendClick(g, a)), !1)
}, FastClick.prototype.onTouchCancel = function() {
  "use strict";
      this.trackingClick = !1, this.targetElement = null
}, FastClick.prototype.onMouse = function(a) {
  "use strict";
      return this.targetElement ? a.forwardedTouchEvent ? !0 : a.cancelable && (!this.needsClick(this.targetElement) || this.cancelNextClick) ? (a.stopImmediatePropagation ? a.stopImmediatePropagation() : a.propagationStopped = !0, a.stopPropagation(), a.preventDefault(), !1) : !0 : !0
}, FastClick.prototype.onClick = function(a) {
  "use strict";
      var b;
      return this.trackingClick ? (this.targetElement = null, this.trackingClick = !1, !0) : "submit" === a.target.type && 0 === a.detail ? !0 : (b = this.onMouse(a), b || (this.targetElement = null), b)
}, FastClick.prototype.destroy = function() {
  "use strict";
      var a = this.layer;
      this.deviceIsAndroid && (a.removeEventListener("mouseover", this.onMouse, !0), a.removeEventListener("mousedown", this.onMouse, !0), a.removeEventListener("mouseup", this.onMouse, !0)), a.removeEventListener("click", this.onClick, !0), a.removeEventListener("touchstart", this.onTouchStart, !1), a.removeEventListener("touchmove", this.onTouchMove, !1), a.removeEventListener("touchend", this.onTouchEnd, !1), a.removeEventListener("touchcancel", this.onTouchCancel, !1)
}, FastClick.notNeeded = function(a) {
  "use strict";
      var b;
      if ("undefined" == typeof window.ontouchstart) return !0;
      if (/Chrome\/[0-9]+/.test(navigator.userAgent)) {
        if (!FastClick.prototype.deviceIsAndroid) return !0;
        if (b = document.querySelector("meta[name=viewport]"), b && -1 !== b.content.indexOf("user-scalable=no")) return !0
      }
      return "none" === a.style.msTouchAction ? !0 : !1
}, FastClick.attach = function(a) {
  "use strict";
      return new FastClick(a)
}, "undefined" != typeof define && define.amd ? define(function() {
  "use strict";
return FastClick
}) : "undefined" != typeof module && module.exports ? (module.exports = FastClick.attach, module.exports.FastClick = FastClick) : window.FastClick = FastClick, $(document).ready(function() {
  $.getScript("//maps.google.com/maps/api/js?sensor=false&async=2&callback=googleMapsLoaded", function() {}), window.googleMapsLoaded = function() {
    initRichMarker(), appInit()
  }
});
var deviceAgent = navigator.userAgent.toLowerCase();
apiKey = "";
var cookieName = "RoadsterRoutesv1.1",
appDomain = "http://www.uml.edu",
cookie = {
  viewedUpdates: []
},
mobileDevice = !1,
tabletDevice = !1,
bounds = null,
hash = [],
lastHash = [],
lastZoom = 0,
flyOutOpen = !1,
searchOpen = !1,
quickLinksContent = "",
busStops = [],
buses = [],
busMarkers = [],
busTimeouts = [],
busAnimations = [],
busPositionBuffers = {},
busLastAngles = {},
currentRouteID = "",
polyline = null,
selectedLineId = 0,
selectedLine = null,
currentBuses = [],
busUpdateTimeout = null,
shouldShowDisclaimer = !1,
apiKey = "87C6ACB0-C2A4-460A-AAF2-9493BAA3917B",
appInit = function() {
  polyline = new google.maps.Polyline({
    editable: !1,
    strokeOpacity: 1,
    strokeWeight: 5
  }), polyline.setMap(map), appDomain = "";
  try {
    null == $.cookie(cookieName) ? $.cookie(cookieName, cookie) : cookie = $.cookie(cookieName)
  } catch (error) {
    if (error.code !== DOMException.QUOTA_EXCEEDED_ERR || 0 !== storage.length) throw error
  }
  if (shouldShowDisclaimer = !cookie.viewedDisclaimer, updateAccordian(), 1 == $.browser.msie && "8" == $.browser.version.split(".")[0] && $("html").addClass("ie8"), deviceAgent.match(/(iphone|ipod|ipad|android)/)) {
    if ($('head link[href*="desktop"]').remove(), disableBodyScroll(), mobileDevice = !0, deviceAgent.match(/(ipad)/) && (tabletDevice = !0, $("#locationButton").remove(), $("body").removeClass("choose"), $("body").addClass("open")), window.onorientationchange = function() {
      OrientationChange()
    }, -1 != deviceAgent.indexOf("crios") || (window.addEventListener("load", function() {
      window.pageYOffset || hideAddressBar()
    }), window.onorientationchange = hideAddressBar, 1 == window.navigator.standalone), "Win32" != navigator.platform) {
      new FastClick(document.body)
    }
    var startX, offsetX, diffX, el = $("#screen"),
    slidePosition = 0,
    touchEl = $("#menuButton");
    touchEl[0].addEventListener("touchstart", function(e) {
      e.preventDefault(), $("#screen").addClass("dragging"), slidePosition = $("body").hasClass("open") ? 260 : 0, el.css("-webkit-transform", "translate3d(" + slidePosition + "px, 0, 0)"), offsetX = ($(window).width() - el.outerWidth(!0)) / 2, startX = e.targetTouches[0].pageX - offsetX
    }, !1), touchEl[0].addEventListener("touchmove", function(e) {
      e.preventDefault(), diffX = e.changedTouches[0].pageX - offsetX - startX, diffX > 260 - slidePosition ? diffX = 260 - slidePosition : 0 - slidePosition > diffX && (diffX = 0 - slidePosition), el.css("-webkit-transform", "translate3d(" + (slidePosition + diffX) + "px, 0, 0)")
    }, !1), touchEl[0].addEventListener("touchend", function(e) {
      e.preventDefault(), $("#screen").removeClass("dragging"), el.css("-webkit-transform", ""), slidePosition += diffX, (Math.abs(slidePosition) > 40 || 0 == Math.abs(slidePosition) || isNaN(slidePosition)) && ($("body").hasClass("open") ? closeFlyOut() : openFlyOut())
    }, !1), touchEl[0].addEventListener("touchcancel", function() {
      $("#screen").removeClass("dragging"), el.css("-webkit-transform", ""), slidePosition += diffX, $("body").hasClass("open") ? closeFlyOut() : openFlyOut()
    }, !1)
  } else $("#mapControlsZoomOut").click(zoomOut), $("#mapControlsZoomIn").click(zoomIn);
  navigator.geolocation ? checkLocation = !0 : $("#locationButton").hide(), loadInitialData(), $("#locationButton").click(function() {
    togglePositioning()
  }), $("#showAllButton").click(function() {
    showAll()
  }), $("#moreInfoDoneButton").click(function() {
    toggleMoreInfo()
  })
},
requireSecondClick = !1,
setRouteTimeout = null,
trackingUser = !1,
locatorHasInit = !1,
updates, updatesContent = [],
fuzzyFacebookTime = function() {
  function fuzzyTime(timeValue, options) {
    var options = options || fuzzyTime.defaultOptions,
    date = parseDate(timeValue),
    delta = parseInt(((new Date).getTime() - date.getTime()) / 1e3),
    relative = options.relativeTime,
    cutoff = +relative === relative ? 60 * relative * 60 : 1 / 0;
    if (relative === !1 || delta > cutoff) return formatTime(date, options) + " " + formatDate(date, options);
    if (60 > delta) return "less than a minute ago";
    var minutes = parseInt(delta / 60 + .5);
    if (1 >= minutes) return "about a minute ago";
    var hours = parseInt(minutes / 60 + .5);
    if (1 > hours) return minutes + " minutes ago";
    if (1 == hours) return "about an hour ago";
    var days = parseInt(hours / 24 + .5);
    if (1 > days) return hours + " hours ago";
    if (1 == days) return formatTime(date, options) + " yesterday";
    var weeks = parseInt(days / 7 + .5);
    if (2 > weeks) return formatTime(date, options) + " " + days + " days ago";
    var months = parseInt(weeks / 4.34812141 + .5);
    if (2 > months) return weeks + " weeks ago";
    var years = parseInt(months / 12 + .5);
    return 2 > years ? months + " months ago" : years + " years ago"
  }

  function parseDate(str) {
    return new Date(Date.parse(str))
  }

  function formatTime(date, options) {
    var h = date.getHours(),
    m = "" + date.getMinutes(),
    am = options.amPm;
    return (h > 12 ? h - 12 : h) + ":" + (1 == m.length ? "0" : "") + m + " " + (12 > h ? am[0] : am[1])
  }

  function formatDate(date, options) {
    var mon = options.monthNames[date.getMonth()],
    day = date.getDate(),
    year = date.getFullYear(),
    thisyear = (new Date).getFullYear(),
    suf = options.ordinalSuffix(day);
    return mon + " " + day + suf + (thisyear != year ? ", " + year : "")
  }
  return fuzzyTime.defaultOptions = {
    relativeTime: 48,
    monthNames: ["Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"],
    amPm: ["AM", "PM"],
    ordinalSuffix: function(n) {
      return ["th", "st", "nd", "rd"][4 > n || n > 20 && 4 > n % 10 ? n % 10 : 0]
    }
  }, fuzzyTime
}(),
myLatLng, myOptions, map, userLocationMarker, geocoder, styles = [{
  featureType: "poi",
  elementType: "labels",
  stylers: [{
    visibility: "on"
  }]
}, {
  stylers: [{}, {
    saturation: -50
  }, {
    lightness: 20
  }]
}, {
  featureType: "road",
  elementType: "geometry",
  stylers: [{
    lightness: 0
  }, {
    visibility: "on"
  }]
}, {
  featureType: "all",
  stylers: []
}, {
  featureType: "poi.park",
  elementType: "labels",
  stylers: [{
    visibility: "off"
  }]
}, {
  featureType: "road",
  stylers: [{
    visibility: "on"
  }]
}, {
  featureType: "water",
  stylers: [{
    visibility: "on"
  }, {
    hue: "#00919f"
  }, {
    saturation: -30
  }, {
    lightness: -10
  }]
}, {
  featureType: "road",
  elementType: "labels",
  stylers: [{
    visibility: "on"
  }]
}],
checkLocation = !1,
positionTimer, locationMarker;