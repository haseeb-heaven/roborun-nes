/*
This extension exports Tiled map level data as C/C++ format in single file $(fileName.h) 
later that can be imported in your project directly by including that file.
Extension : Export C/C++ list. 
Author: Haseeb Mir
Tool: Tiled (1.4.3)
Copyleft@ 2021

Usage: 
1)Place this file in your extensions folder.
2)Open your map in Tiled editor and export data (File -> Export -> Export As -> C/C++ format)
3)Save your file. 

Extensions folder path for different OS.
Windows     C:/Users/<USER>/AppData/Local/Tiled/extensions/
macOS       ~/Library/Preferences/Tiled/extensions/
Linux       ~/.config/tiled/extensions/
*/

//Method to export multi-map (Map with multiple rooms)
function multiMapExportCpp(filePath, map) {

    //Setting absolute file path and name.
    var fileNameExt = filePath.replace(/^.*[\\\/]/, '');
    var fileName = fileNameExt.split('.').slice(0, -1).join('.');

    var file = new TextFile(filePath, TextFile.WriteOnly);

    //Writing export header .
    var exportHeader = "/*File: " + fileNameExt + "\n" +
        "Map Type: Multi Room [width: " + map.width + ",height: " + map.height + "] " + "\n" +
        "Exported: Using Tiled(C/C++) plugin by Haseeb Mir\n" + "*/\n";

    file.write(exportHeader);    
    var loops = map.width / 16; //force int division
    var a = 0,k=0;

    //Writing export data.
    for (var l = 0; l < map.layerCount; ++l,++k) {
        var layer = map.layerAt(l);
        if (layer.isTileLayer) {
            for (var h = 0; h < loops; h++) {
                file.write("const unsigned char " + fileName + "_" + k + "[]=\n{\n")
                for (var i = 0; i < layer.height; i++) {
                    for (var j = 0; j < 16; j++) {
                        a = j + (h * 16);
                        file.write(layer.cellAt(a,i).tileId);
                        file.write((i < layer.height - 1 || j < 16 - 1) ? "," : "");
                    }
                    file.write("\n");
                }
                file.write("\n};\n\n");
                k++;
            }
        }
    }

    //Adding data to list.
    file.write("const unsigned char* const " + fileName + "_list[]=\n{\n");
    for (var i = 0; i < loops; ++i) {
        file.write(fileName + "_" + i);
        if (loops > 1 && i < loops - 1)
            file.write(",");
    }
    file.write("\n};\n");
    tiled.alert("Exporting data finished");
    file.commit();
};

//Method to export single-map (Map with single room)
function singleMapExportCpp(filePath, map) {

    //Setting absolute file path and name.
    var fileNameExt = filePath.replace(/^.*[\\\/]/, '');
    var fileName = fileNameExt.split('.').slice(0, -1).join('.');

    var file = new TextFile(filePath, TextFile.WriteOnly);

    //Writing export header .
    var exportHeader = "/*File: '" + fileNameExt + "\n" +
        "Map Type: Single Room [width: " + map.width + ",height: " + map.height + "] " + "\n" +
        "Exported: Using Tiled(C/C++) plugin by Haseeb Mir\n" + "*/\n"
    file.write(exportHeader);

    //Writing export data.
    for (var i = 0; i < map.layerCount; ++i) {
        file.write("const unsigned char " + fileName + "_" + i + "[]=\n{\n");
        var layer = map.layerAt(i);
        if (layer.isTileLayer) {
            for (y = 0; y < layer.height; ++y) {
                for (x = 0; x < layer.width; ++x) {
                    file.write(layer.cellAt(x, y).tileId);
                    file.write((y < layer.height - 1 || x < layer.width - 1) ? "," : "");
                }
                file.write("\n");
            }
        }
        file.write("\n};\n\n");
    }

    //Adding data to list.
    file.write("const unsigned char* const " + fileName + "_list[]=\n{\n");
    for (var i = 0; i < map.layerCount; ++i) {
        file.write(fileName + "_" + i);
        if (map.layerCount > 1 && i < map.layerCount - 1)
            file.write(",");
    }
    file.write("\n};\n");
    tiled.alert("Exporting data finished");
    file.commit();
};

//Main Export method.
var cppExportFormat = {
    name: "C/C++ format",
    extension: "h",

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
            singleMapExportCpp(filePath, map);
        else if (mapType == 1)
            multiMapExportCpp(filePath, map);

    },
}

tiled.registerMapFormat("C/C++ format", cppExportFormat);