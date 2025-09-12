model BasicBuilder -ndm 3 -ndf 6
pset w 144.0
node 2 0 0 576 -mass $w $w  0.0  0.0  0.0  0.0
fix 2 0 0 1 1 1 0 
node 1 0 0 0 
fix 1 1 1 1 1 1 1 
uniaxialMaterial Steel01 1 1e+06 100 0.1
uniaxialMaterial Steel01 2 1e+06 100 0.1
uniaxialMaterial Elastic 3 1e+10
element zeroLength 1 1 2 -mat 1 2 3 -dir 1 2 6 -doRayleigh
