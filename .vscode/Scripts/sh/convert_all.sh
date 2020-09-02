#!/bin/bash
#                    SCRIPT NAME                INTPUT LOCATION    OUTPUT   CLEAR?
#----------------------------------------------|------------------|--------|------|
./.vscode/Scripts/sh/convert_affine.sh          $1/affine          $2       false
./.vscode/Scripts/sh/convert_backgrounds.sh     $1/backgrounds     $2       false
./.vscode/Scripts/sh/convert_bitmap8.sh         $1/bitmap8         $2       false
./.vscode/Scripts/sh/convert_bitmap8_shared.sh  $1/bitmap8_shared  $2       false
./.vscode/Scripts/sh/convert_bitmap16.sh        $1/bitmap16        $2       false
./.vscode/Scripts/sh/convert_cmaps.sh           $1/cmaps           $2       false
./.vscode/Scripts/sh/convert_fonts.sh           $1/fonts           $2       false
./.vscode/Scripts/sh/convert_sprites.sh         $1/sprites         $2       false
./.vscode/Scripts/sh/convert_sprites_autopal.sh $1/sprites_autopal $2       false