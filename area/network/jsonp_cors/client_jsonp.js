// http://jsfiddle.net/sWaSP/

$.ajax({
  url: "http://api_test_server.proudlygeek.c9.io/?callback=?",
  dataType: "jsonp",
  success: function(data) {
    console.log(data);
  }
});
