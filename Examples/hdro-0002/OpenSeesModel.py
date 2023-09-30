ops.wipe()


numDOF=6

ops.model('basic','-ndm',3,'-ndf',numDOF)

targetNatFreq=2.19 #hz

mass=1286.4 #kg

#lambda= k/m
# omega = sqrt(lambda)
# fn = omega/(2pi)

# fn*2pi=omega
# omega^2 = lambda
# lambda=k/m
# lambda*m=k

# k = (fn*2pi)**2 * mass

E=(((2*np.pi)*targetNatFreq)**2)*mass

ops.node(1, 60.0, 0, 2.25)
ops.node(2, 60.0, 0, 2.25)

# nodal mass (weight / g):
ops.mass(2, mass,  mass,  mass,0,0,0)
ops.mass(1, mass,  mass,  mass,mass,mass,mass)

# Define material
matTag = 1
#ops.nDMaterial('ElasticIsotropic', matTag,*[SDOFSTIFFNESS, 0.3])

# Assign zero length element
vecx=[1,0,0]
vecyp=[0,0,1]
eleTag=1
eleNodes=[1,2]

secTag=1
quantity='P'
ops.uniaxialMaterial('Elastic', matTag, E)
ops.section('Uniaxial', secTag, matTag, quantity)
#ops.element('zeroLengthND', 1, *[1, 2], matTag,'-orient', *vecx, *vecyp)
ops.element('zeroLengthSection', eleTag, *eleNodes, secTag, '-orient', *vecx, *vecyp)

ops.fix(1,*[1,1,1,1,1,1])
ops.fix(2,*[0,1,1,1,1,1])

# coupledNodes=[1] # in this case, the boundary doesnt move...

coupledNodes=[2] # in this case, the boundary is moving as a rigid body...


#Lambda = ops.eigen('-genBandArpack',1) # eigenvalue mode 1
# Lambda = ops.eigen('-fullGenLapack',1) # eigenvalue mode 1

# omegaN=np.sqrt(Lambda[0])

# with open('SysInfo.txt', 'w') as f:
	# print('EIGENVALUEs: ', Lambda, '\n frequency ', omegaN, 'rads/sec', '\n frequency ', omegaN/(2*np.pi), 'Hz', '\nFIRST mode PERIODs: ', 2*np.pi/omegaN, ' s',file=f)


