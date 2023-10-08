
FOAMySeesInstance.osi=ops.model('basic','-ndm',3,'-ndf',6)

RunEQ=0

nElem=16

nu=0.45

EScaleFactor=1
E=1000000*EScaleFactor #10^7 dyne or 1MPa

structuralDensity=2500
MASS=structuralDensity*0.5*0.05*0.05*3.1415

beamNormal=[1., 0., 0.]

structuralDensity=2500
node1=[1.5,0.00,0.00]
node2=[1.5,0.00,0.5]

I=3.1415*(0.05**4)/4
A = 0.05*0.05*3.1415
Iz = I
Iy = Iz
J =  3.1415*(0.1**4)/32
beamLength=node2[1]-node1[1]

G=E/(2*(1+nu))

sigmaY=1e8
H_iso=0.5 
H_kin=0.25


matTag=1

# ops.nDMaterial('ElasticIsotropic', matTag, E, nu, 0.0)



# node1=[2.0,0.0,0.0]
# node2=[2.0,0.0,0.25]

beamNormal=[-1,0,0]


xNodeList=np.linspace(node1[0],node2[0],nElem+1)
yNodeList=np.linspace(node1[1],node2[1],nElem+1)
zNodeList=np.linspace(node1[2],node2[2],nElem+1)


for nodeNum in range(0, len(xNodeList)):
	ops.node(nodeNum, xNodeList[nodeNum],yNodeList[nodeNum],zNodeList[nodeNum])

# ##################
# ELEMENTS
# ##################


matTag=1
K=E*G/(3*(3*G - E))



ops.uniaxialMaterial('Elastic', matTag, E) 
#ops.uniaxialMaterial('ElasticPP', matTag, E, 0.05)

#ops.uniaxialMaterial('ElasticMultiLinear', matTag, 0.0, '-strain', *[-0.3,-0.2,-0.1,0,0.1,0.2,0.3], '-stress', *[-0.3*E,-0.2*E,-0.1*E,0,0.1*E,0.2*E,0.3*E])

#ops.uniaxialMaterial('MultiLinear', matTag, *[0.001, E*0.001, 0.2, E*0.15])

#ops.uniaxialMaterial('Hardening', matTag, E, sigmaY, H_iso, H_kin)
#ops.nDMaterial('ElasticIsotropic', matTag, E, nu, 1000.0)
#ops.nDMaterial('J2Plasticity', matTag, K, G, sig0, sigInf, delta, H)

# coordTransf = 'Corotational'
coordTransf='PDelta'
#coordTransf='Linear'
#############################

nodeList=ops.getNodeTags()

nodeLocs=np.zeros([len(nodeList),3])

nodalMass=MASS/len(nodeLocs)
secTag=1
matTag=1

ops.section('Elastic', secTag, E, A, Iz, Iy, G, J)

#ops.section('Fiber', secTag, '-GJ', G*J)

#ops.patch('rect', matTag, 2,12, *[-0.005,-0.006], *[0.005,0.006])

for node in range(1,len(nodeList)):
	
	nodeLocs[node,:]=ops.nodeCoord(nodeList[node])

integTag=1
ops.beamIntegration('Legendre', integTag, secTag, 2)

leme=10/(len(xNodeList)-1)
nodRotMass=0 #(1/12)*nodalMass*(leme**2)
for node_num in range(len(nodeLocs)):
	ops.mass(nodeList[node_num],*[nodalMass,nodalMass,nodalMass,nodRotMass,nodRotMass,nodRotMass])		
for nodeNum in range(1,len(nodeLocs)):
	ops.geomTransf(coordTransf, nodeNum+100000, beamNormal[0],beamNormal[1],beamNormal[2])
	
	#ops.element('forceBeamColumn', nodeNum, *[nodeNum-1, nodeNum], nodeNum+100000, integTag, '-iter', 10, 1e-12)#, '-mass', mass=0.0)
	#ops.element('elasticBeamColumn', nodeNum, *[nodeNum-1, nodeNum], secTag, nodeNum+100000)
	ops.element('dispBeamColumn', nodeNum, *[nodeNum-1, nodeNum], nodeNum+100000, secTag) #, '-cMass', '-mass', mass=0.0)
	#ops.element('elasticBeamColumn', nodeNum, nodeNum-1, nodeNum, A, E, G, J, Iy, Iz, nodeNum+100000)
	#ops.element('nonlinearBeamColumn', nodeNum, *[nodeNum-1, nodeNum],5,secTag,nodeNum+100000,'-iter', secTag)

ops.fixZ(0.00,*[1,1,1,1,1,1])



