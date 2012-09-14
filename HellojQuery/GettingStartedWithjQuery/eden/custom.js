$(document).ready(function () {
    $('#faq').find('dd').hide().end().find('dt').click(function () {
        var answer = $(this).next();
        if (answer.is(':visible')) {
            answer.slideUp();
        } else {
            answer.slideDown();
        }
    });
});