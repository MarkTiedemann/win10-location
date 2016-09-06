
NodeRTCmd `
    --namespace 'Windows.Devices.Geolocation' `
    --winmd 'C:\Program Files (x86)\Windows Kits\10\UnionMetadata\Windows.winmd' `
    --outdir ($PsScriptRoot + '\prebuilt')
