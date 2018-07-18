if($.cookie("reason-color")) {
    $("link[href|='../assets/css/style']").attr("href","../assets/css/" + $.cookie("reason-color"));
}

if($.cookie("reason-width")) {
    $("link[href|='../assets/css/width']").attr("href","../assets/css/" + $.cookie("reason-width"));
}

$(document).ready(function() {
    $("#color-options .color-box").click(function() {
        $("link[href|='../assets/css/style']").attr("href", "../assets/css/" + $(this).attr('rel'));
        $("link[href|='../assets/css/style']").attr("href", "../assets/css/" + $(this).attr('rel'));
        $.cookie("reason-color",$(this).attr('rel'), {expires: 7, path: '/'});
        return false;
    });

    $("#width-options .container-option").click(function() {
        $("link[href|='../assets/css/width']").attr("href", "../assets/css/" + $(this).attr('rel'));;
        $.cookie("reason-width",$(this).attr('rel'), {expires: 7, path: '/'});
        return false;
    });
});
