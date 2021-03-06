#include "project.h"

#include <qgsproject.h>
#include <qgslayertree.h>

Project* Project::sInstance = 0;

Project::Project(QObject *parent)
  : QObject(parent)
{

}


Project* Project::instance()
{
  if (!sInstance)
    sInstance = new Project();
  return sInstance;
}

void Project::setProjectFile(const QString& filename)
{
  mFilename = filename;

  QgsProject::instance()->setFileName(filename);
  bool res = QgsProject::instance()->read();
  qDebug("load project: %d", res);

  emit projectFileChanged();
}

QStringList Project::layers() const
{
  QgsLayerTreeGroup* root = QgsProject::instance()->layerTreeRoot();
  //qDebug("root: %s", root->dump().toLocal8Bit().data());
  QStringList list;
  foreach (QgsLayerTreeLayer* nodeLayer, root->findLayers())
  {
    if (nodeLayer->isVisible() == Qt::Checked)
      list << nodeLayer->layerId();
  }

  return list;
}
