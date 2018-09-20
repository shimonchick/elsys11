function addItem(){
    var items = document.getElementById("list");
    var itemName = document.getElementById('itemName').value;
    var item = createItem(itemName)

    items.appendChild(item);
}

function createItem(itemName){
    var item = document.createElement("li");
    var itemId = "_" + itemName;
    item.id = itemId;
    item.appendChild(document.createTextNode(itemName + " "));
    
    var removeLink = document.createElement("a");
    removeLink.href = "#";
    removeLink.appendChild(document.createTextNode("remove"));
    removeLink.onclick = function(){removeItem(itemId)}
    item.appendChild(removeLink);
    return item;
}

function removeItem(itemId){
    var item = document.getElementById(itemId);
    var itemParent = item.parentNode;
    itemParent.removeChild(item);
}