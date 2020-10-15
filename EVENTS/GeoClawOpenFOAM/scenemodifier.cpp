//*********************************************************************************
// In this routines related scenemodifier class for QT3D
//*********************************************************************************

//*********************************************************************************
// Include user headers
//*********************************************************************************
#include "scenemodifier.h"

//*********************************************************************************
// Scenemodifier starts here
//*********************************************************************************
SceneModifier::SceneModifier(Qt3DCore::QEntity *rootEntity)
    : m_rootEntity(rootEntity)
{

    // New code
    Qt3DRender::QMesh * ModelMesh = new Qt3DRender::QMesh();
    ModelMesh->setSource(QUrl::fromLocalFile("/Users/ajaybh/Desktop/lamp.stl"));

    //Model Transform
    Qt3DExtras::QPhongMaterial *ModelMaterial = new Qt3DExtras::QPhongMaterial();
    //ModelMaterial->setDiffuse(QColor(QRgb(0x665423)));
    ModelMaterial->setDiffuse(QColor(255, 0, 0, 127));

    // Transform and scale: Need better metrics here based on model size
    Qt3DCore::QTransform *ModelTransform = new Qt3DCore::QTransform();
    ModelTransform->setScale(0.025f);
    ModelTransform->setTranslation(QVector3D(0.0f, -4.0f, -1.0f));

    // Model
    m_userobject = new Qt3DCore::QEntity(m_rootEntity);
    m_userobject->addComponent(ModelMesh);
    m_userobject->addComponent(ModelMaterial);
    m_userobject->addComponent(ModelTransform);

}

//*********************************************************************************
// Delete scenemodifier
//*********************************************************************************
SceneModifier::~SceneModifier()
{

}

//*********************************************************************************
// Enable user object
//*********************************************************************************
void SceneModifier::enableuserobject(bool enabled)
{
    m_userobject->setEnabled(enabled);
}

