// ADDED
$(function() {

    // Compare by substrings when length has focus
    $('input[name=length]').focus(function() {
        $('input[name=compare][value=substrings]').prop('checked', true);
    });

});
