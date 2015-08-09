var File = loadExtension("qbs.File");
var FileInfo = loadExtension("qbs.FileInfo");
var ModUtils = loadExtension("qbs.ModUtils");
var PathTools = loadExtension("qbs.PathTools");


function toolPath(product, tool) {
    var linkerPath = product.moduleProperty('cpp', "linkerPath");
    var toolchainInstallPath = FileInfo.path(product.moduleProperty("cpp", "linkerPath")) + "/";

    var toolchainPrefix = '';
    var toolchainSuffix = '';
    if (linkerPath.contains(".exe")) {
        toolchainSuffix = '.exe';
    }

    if (linkerPath.contains("arm-none-eabi-")) {
        toolchainPrefix = "arm-none-eabi-";
    } else {
        toolchainPrefix = "arm-eabi-";
    }
    print(Object.getOwnPropertyNames(product));
    return toolchainInstallPath + toolchainPrefix + tool + toolchainSuffix;
}


