$(document).ready(function () {
    $('#btnAddItem').click(function () { 
        var itemId = $('#itemName').val();
        var item = $("<li/>", { text: itemId,
                                id: '_' + itemId});
        var remove = $('<a id="' + itemId + '" href="#">remove</a>');
        $(remove).click(function(){
            $('#_' + itemId).remove();
        });
        item.append(" ");
        item.append(remove);
        $('#list').append(item);     
        
    });
});