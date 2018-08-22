document.addEventListener("DOMContentLoaded", function(event) {
  var p = document.createElement("p");
  p.appendChild(document.createTextNode("This element was made by script."));
  document.body.appendChild(p);
});