set numNode [llength [getNodeTags]]
set numEle [llength [getEleTags]]

recorder EnvelopeNode -file disp.out -nodeRange 1 $numNode  -dof 1 2 disp
recorder NodeRMS -file accel.out -nodeRange 1 $numNode -dof 1 2 accel
recorder EnvelopeElement -file forces.out -eleRange 1 $numEle forces
recorder EnvelopeElement -file pressures.out -eleRange 1 $numEle forces