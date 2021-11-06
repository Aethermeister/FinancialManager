param([String]$target="debug")

$global:targetPath = ""
function PrintInformation {
    param (
        [String]$Message
    )
    
    Write-Output ""
    Write-Output $Message
    Write-Output ""
}

function RunWinDeployQt {
    if($target -eq "debug") {
        $global:targetPath = "..\Build\Debug\"

        PrintInformation -Message "Run Qt deploy for debug build"
    }
    elseif($target -eq "release") {
        $global:targetPath = "..\Build\Release\"

        PrintInformation -Message "Run Qt deploy and install framework for release build"
    }

    $deployRelevantFiles = "FinancialManagerLibrary.dll", "FinancialManagerAutoTest.exe"

    foreach ($file in $deployRelevantFiles) {
        PrintInformation -Message "Call windeplyqt on"
        & $env:QTDEPLOY $global:targetPath$file
    }
}

function PrepareInstallerFramework {
    $installDataFolder = ".\InstallerFramework\packages\com.aetherprojects.financialmanager\data"
    $installerDestination = "..\Installer"
    
    PrintInformation -Message "Installer data cleanup"
    Remove-Item -Path $installDataFolder -Recurse -Force
    New-Item -Path $installDataFolder -ItemType Directory

    if(Test-Path $installerDestination) { Remove-Item -Path $installerDestination -Recurse -Force }
    New-Item -Path $installerDestination -ItemType Directory
    Copy-Item -Path ".\readme.txt" -Destination $installerDestination
    
    PrintInformation -Message "Copying application files to installer data folder"
    Copy-Item -Path $targetPath"*" -Destination $installDataFolder -Recurse
    Get-ChildItem -Path $installDataFolder
}

RunWinDeployQt
if($target -eq "release") {
    PrepareInstallerFramework

    Set-Location .\InstallerFramework

    $installerDestination = "..\..\Installer\"
    $infoMessage = "Creating installer executable at " + $installerDestination
    PrintInformation -Message $infoMessage
    & $env:QTINSTALL --offline-only -c config/config.xml -p packages $installerDestination\FinancialManagerInstaller.exe
    PrintInformation -Message "Done"
}