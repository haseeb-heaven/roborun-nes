/*
This extension exports Tiled map level data as Assembly (6502) data format in single file $(fileName.asm) 
later that can be imported in your project directly by including that file.
Extension : Export Assembly data. 
Author: Haseeb Mir
Tool: Tiled (1.4.3)
Copyleft@ 2021

Usage: 
1)Place this file in your extensions folder.
2)Open your map in Tiled editor and export data (File -> Export -> Export As -> Assembly (6502) format)
3)Save your file. 

Extensions folder path for different OS.
Windows     C:/Users/<USER>/AppData/Local/Tiled/extensions/
macOS       ~/Library/Preferences/Tiled/extensions/
Linux       ~/.config/tiled/extensions/
*/

//Method to export multi-map (Map with multiple rooms)
function multiMapExportAsm(filePath, map) {
    //Setting absolute file path and name.
    var fileNameExt = filePath.replace(/^.*[\\\/]/, '');
    var fileName = fileNameExt.split('.').slice(0, -1).join('.');

    var file = new TextFile(filePath, TextFile.WriteOnly);

    //Writing export header .
    var exportHeader = ";File: '" + fileNameExt + "\n" +
        ";Map Type: Multi Room [width: " + map.width + ",height: " + map.height + "] " + "\n" +
        ";Exported: Using Tiled(Assembly 6502) plugin by Haseeb Mir\n" + "\n"
    file.write(exportHeader);

    var loops = map.width / 16; //force int division
    var a = 0,k=0;

    //Writing export data.
    for (var l = 0; l < map.layerCount; ++l,++k) {
        var layer = map.layerAt(l);
        if (layer.isTileLayer) {
            for (var h = 0; h < loops; h++) {
                file.write(fileName + "_" + k + ":\n.byte ");
                for (var i = 0; i < layer.height; i++) {
                    for (var j = 0; j < 16; j++) {
                        a = j + (h * 16);                
                        file.write("$" + layer.cellAt(a, i).tileId);
                        file.write((i < layer.height - 1 || j < 16 - 1) ? "," : "");
                    }
                }
                file.write("\n\n");
                k++;
            }
        }
    }

    //Adding data to list.
    file.write(fileName + "_list:\n.addr :");
    for (var i = 0; i < loops; ++i) {
        file.write(fileName + "_" + i);
        if (loops > 1 && i < loops - 1)
            file.write(",");
    }
    file.write("\n");
    tiled.alert("Exporting data finished");
    file.commit();
};

//Method to export single-map (Map with single room)
function singleMapExportAsm(filePath, map) {

    //Setting absolute file path and name.
    var fileNameExt = filePath.replace(/^.*[\\\/]/, '');
    var fileName = fileNameExt.split('.').slice(0, -1).join('.');

    var file = new TextFile(filePath, TextFile.WriteOnly);

    //Writing export header .
    var exportHeader = ";File: '" + fileNameExt + "\n" +
        ";Map Type: Single Room [width: " + map.width + ",height: " + map.height + "] " + "\n" +
        ";Exported: Using Tiled(Assembly 6502) plugin by Haseeb Mir\n" + "\n"
    file.write(exportHeader);

    //Writing export data.
    for (var i = 0; i < map.layerCount; ++i) {
        file.write(fileName + "_" + i + ":\n.byte ");
        var layer = map.layerAt(i);
        if (layer.isTileLayer) {
            for (y = 0; y < layer.height; ++y) {
                for (x = 0; x < layer.width; ++x) {
                    file.write("$" + layer.cellAt(x, y).tileId);
                    file.write((y < layer.height - 1 || x < layer.width - 1) ? "," : "");
                }
            }
        }
        file.write("\n\n");
    }

    //Adding data to list.
    file.write(fileName + "_list:\n.addr :");
    for (var i = 0; i < map.layerCount; ++i) {
        file.write(fileName + "_" + i);
        if (map.layerCount > 1 && i < map.layerCount - 1)
            file.write(",");
    }
    file.write("\n");
    tiled.alert("Exporting data finished");
    file.commit();
};

//Main Export method.
var asmExportFormat = {
    name: "Assembly format (6502)",
    extension: "asm",

    write: function (map, filePath) {

        var mapType = 0;//Single=0,Multi=1
        mapType = map.width > 16 ? 1 : 0;

        //Check map properties. 
        if (map.width < 16) {
            tiled.alert("File too small to handle.", "Export error");
            return;
        }

        if ((map.width & 0x0f) != 0)
            tiled.alert("Warning expected width divisible by 16.");

        if (mapType == 0)
            singleMapExportAsm(filePath, map);
        else if (mapType == 1)
            multiMapExportAsm(filePath, map);

    },
}

tiled.registerMapFormat("Assembly format (6502)", asmExportFormat);