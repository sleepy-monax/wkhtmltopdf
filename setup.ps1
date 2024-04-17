function Get-Github-Release {
    param(
        [string]$repo,
        [string]$output
    )

    $url = Invoke-WebRequest -Uri "https://api.github.com/repos/$repo/releases/latest" | ConvertFrom-Json `
        | Select-Object -ExpandProperty assets `
        | Select-Object -ExpandProperty browser_download_url `
        | Where-Object { $_ -like "*.msi" }

    Invoke-WebRequest -Uri $url -OutFile $output
}


New-Item -Path "$env:TEMP\wkhtmltopdf" -ItemType 'directory' -Force | Out-Null

if ((Get-Command -Name "perl" -ErrorAction SilentlyContinue) -eq $null) {
    Write-Debug "Downloading Perl..."
    Get-Github-Release "StrawberryPerl/Perl-Dist-Strawberry" "$env:TEMP\wkhtmltopdf\strawberry.msi"
}

Get-ChildItem "$env:TEMP\wkhtmltopdf" -Filter "*.msi" | ForEach-Object {
    Start-Process -FilePath $_.FullName -ArgumentList "/passive /norestart" -Wait
}

Remove-Item -Path "$env:TEMP\wkhtmltopdf" -Recurse -Force
Write-Host "Setup is done! Don't forget to restart your shell before running build.ps1."
