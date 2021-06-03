#units kip, in

# variable parameter
pset w 2200.0
pset k 1600.0


# constants
set g 386.1;  
set b 1800.
set d 1800.
set h 1440.
set numStory 9
set bW 20000.0;                   # building Weight

# derived parameters
set sH [expr $h/(1.*$numStory)];  # story Height
set fM [expr $w/$g];             # floor translational mass
set sM 1.0e-3;                    # floor rotational mass

# build model
model Basic -ndm 3 -ndf 6
node 1 0. 0. 0.
fix 1 1 1 1 1 1 1
set E 29000.
set A 1e4
set I [expr $k*$sH*$sH*$sH/(12.*$E)]
geomTransf Linear 1 0 1 0
set G 1e4
set J 1e8

for {set i 1; set j 2} {$i <= $numStory} {incr i 1; incr j 1} {
    node $j 0. 0. [expr $i*$sH] -mass $fM $fM $fM $sM $sM $sM
    fix $j 0 0 1 1 1 0
    element elasticBeamColumn $i $i $j $A $E $G $J $I $I 1
}

