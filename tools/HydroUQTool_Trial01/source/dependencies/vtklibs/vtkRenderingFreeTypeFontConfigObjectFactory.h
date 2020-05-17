/*=========================================================================

  Program:   Visualization Toolkit
  Module:    vtkRenderingFreeTypeFontConfigObjectFactory.h

  Copyright (c) Ken Martin, Will Schroeder, Bill Lorensen
  All rights reserved.
  See Copyright.txt or http://www.kitware.com/Copyright.htm for details.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notice for more information.

=========================================================================*/

#ifndef vtkRenderingFreeTypeFontConfigObjectFactory_h
#define vtkRenderingFreeTypeFontConfigObjectFactory_h

#include "vtkRenderingFreeTypeFontConfigModule.h" // For export macro
#include "vtkObjectFactory.h"

class VTKRENDERINGFREETYPEFONTCONFIG_EXPORT vtkRenderingFreeTypeFontConfigObjectFactory : public vtkObjectFactory
{
public:
  static vtkRenderingFreeTypeFontConfigObjectFactory * New();
  vtkTypeMacro(vtkRenderingFreeTypeFontConfigObjectFactory, vtkObjectFactory)

  const char * GetDescription() override { return "vtkRenderingFreeTypeFontConfig factory overrides."; }

  const char * GetVTKSourceVersion() override;

  void PrintSelf(ostream &os, vtkIndent indent) override;

protected:
  vtkRenderingFreeTypeFontConfigObjectFactory();

private:
  vtkRenderingFreeTypeFontConfigObjectFactory(const vtkRenderingFreeTypeFontConfigObjectFactory&) = delete;
  void operator=(const vtkRenderingFreeTypeFontConfigObjectFactory&) = delete;
};

#endif // vtkRenderingFreeTypeFontConfigObjectFactory_h
