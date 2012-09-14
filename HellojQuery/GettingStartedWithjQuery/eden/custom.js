$(document).ready(function () {
    $("a").hover(function () {
        $(this).parents("p").addClass("highlight");
    }, function () {
        $(this).parents("p").removeClass("highlight");
    });
});