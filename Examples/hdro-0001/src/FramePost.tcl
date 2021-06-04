
set dispIn [open disp.out r]
while { [gets $dispIn data] >= 0 } {
     set maxDisp $data
}
set accelIn [open accel.out r]
while { [gets $accelIn data] >= 0 } {
     set maxAccel $data
}
set forceIn [open forces.out r]
while { [gets $forceIn data] >= 0 } {
     set maxForce $data
}

# create file handler to write results to output & list into which we will put results
set resultFile [open results.out w]
set results []

# for each quanity in list of QoI passed
# output data

foreach edp $listQoI {
    set splitEDP [split $edp "_"]	
    set response [lindex $splitEDP 0]
    set tag [lindex $splitEDP 1]
    if {[llength $splitEDP] == 2} {
	set dof 1
    } else {
	set dof [lindex $splitEDP 2]
    }
    
    if {$response == "Disp"} {
	set nodeDisp [lindex $maxDisp [expr (($tag-1)*2)+$dof-1]]
	lappend results $nodeDisp
    } elseif {$response == "RMSA"} {
	set nodeAccel [lindex $maxAccel [expr (($tag-1)*2)+$dof-1]]
	lappend results $nodeAccel
    } elseif {$response == "Force"} {
	set eleForce [lindex $maxForce [expr (($tag-1)*6)+$dof-1]]
	lappend results $eleForce
    } else {
	lappend results 0.0
    }
}

# send results to output file & close the file
puts $resultFile $results
close $resultFile
