$(function () {
    
    // Basic parameters
    var OFFSET = 3;
    var $sectionCache = $("section");
    
    /**
     * Refresh the sidebar active item based on the window scroll
     */
    function refreshSidebar () {
        var scrollTop = $(window).scrollTop();
        var a = 0;
        for (var i = 0; i < $sectionCache.length; i++) {
            var $section = $sectionCache.eq(i);
            var top = $section.offset().top;
            var height = $section.outerHeight();
            if ($("#section-list a[data-sec='#" + $section.attr("id") + "']").length &&
                top < scrollTop + OFFSET && top + height > scrollTop + OFFSET) {
                a = i;
            }
        }
        $("#section-list a").removeClass("active");
        $("#section-list a[data-sec='#" + $sectionCache.eq(a).attr("id") + "']").addClass("active");
    }
    
    /**
     * Window scroll listener to refresh the sidebar
     */
    $(window).scroll(function () {
        refreshSidebar();
    });
    
    /**
     * Sidebar item click listener
     */
    $("#section-list a").click(function () {
        $('html, body').animate({
            scrollTop: $($(this).attr("data-sec")).offset().top
        }, 300);
    });
    
    /**
     * Refresh the sidebar when the page load
     */
    refreshSidebar();
});
