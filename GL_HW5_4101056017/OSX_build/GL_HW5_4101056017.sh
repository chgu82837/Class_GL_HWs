#!/bin/sh

BASEDIR=$(dirname $0)
PROJ_NAME="GL_HW5_4101056017"
cd $BASEDIR

# OBJ options:
# ../$PROJ_NAME/data/Hot_Girl_01.obj
# ../$PROJ_NAME/data/mario_obj.obj
# ../$PROJ_NAME/data/Luigi_obj.obj
# ../$PROJ_NAME/data/vanille_obj.obj
# ../$PROJ_NAME/data/Hulk.ob

./$PROJ_NAME ../$PROJ_NAME/data/Luigi_obj.obj ../$PROJ_NAME/data/vanille_obj.obj ../$PROJ_NAME/data/Hulk.obj
