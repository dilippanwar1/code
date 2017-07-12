function onEdit(e) {
  if (SpreadsheetApp.getActiveSheet().getName() === "招人需求") {
    return;
  }
  var limit = 100;
  if (e.value.length > limit) {
    e.range.setNote(e.value);
    e.range.setValue(e.value.substring(0, limit) + "...");
  }
}

function UpdateSheet() {
  var ss = SpreadsheetApp.getActiveSpreadsheet();
  var sheet = ss.getSheetByName("onhold-准备拒");
  var selection=sheet.getDataRange();
  var columns=selection.getNumColumns();
  var rows=selection.getNumRows();
  for (var column=1; column < columns; column++) {
    for (var row=1; row < rows; row++) {
      var limit = 100;
      var cell = selection.getCell(row,column);
      if (cell.getValue().length > limit) {
        cell.setNote(cell.getValue());
        cell.setValue(cell.getValue().substring(0, limit) + "...");
      }
    }
  }
}
