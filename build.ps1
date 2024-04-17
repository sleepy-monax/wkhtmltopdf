New-Item -Path './build' -ItemType 'directory' -Force | Out-Null
Set-Location -Path './build'

$vswhere = "${env:ProgramFiles(x86)}\Microsoft Visual Studio\Installer\vswhere.exe"
$vars = & $vswhere -latest -requires Microsoft.VisualStudio.Component.VC.Tools.x86.x64 -find **\Auxiliary\Build\vcvars64.bat

cmd /C "`"$vars`" && set > %temp%\vcvars.txt"
Get-Content "$env:temp\vcvars.txt" | Foreach-Object {
  if ($_ -match "^(.*?)=(.*)$") {
    Set-Content "env:\$($matches[1])" $matches[2]
  }
}

../qt/configure.exe `
-opensource -confirm-license -fast -release -static -graphicssystem raster `
-webkit -exceptions -xmlpatterns -system-zlib -system-libpng -system-libjpeg `
-no-libmng -no-libtiff -no-accessibility -no-stl -no-qt3support -no-phonon `
-no-phonon-backend -no-opengl -no-declarative -no-script -no-scripttools `
-no-sql-db2 -no-sql-ibase -no-sql-mysql -no-sql-oci -no-sql-odbc -no-sql-psql `
-no-sql-sqlite -no-sql-sqlite2 -no-sql-tds -no-mmx -no-3dnow -no-sse -no-sse2 `
-no-multimedia -nomake demos -nomake docs -nomake examples -nomake tools `
-nomake tests -nomake translations -mp -qt-style-windows -no-style-cleanlooks `
-no-style-windowsxp -no-style-windowsvista -no-style-plastique -no-style-motif `
-no-style-cde -openssl-linked -platform win32-msvc2015
