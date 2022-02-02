######################################################################
# Select build-in or cloned libqtr2d
######################################################################

#--------------------------------------------------------------------
with_external_libqtr2d|with_builtin_libqtr2d {
      message( "Configuring user-selected libqtr2d" )
} else {

     exists(../../libqtr2d/libqtr2d/libqtr2d.pro) {
          message( "Configuring external libqtr2d" )
          CONFIG += with_external_libqtr2d
    } else {
          message( "Configuring built-in libqtr2d" )
          CONFIG += with_builtin_libqtr2d
    }
}



#--------------------------------------------------------------------
with_external_libqtr2d {
    QTR2dPATH = ../../libqtr2d/libqtr2d
    include(../../libqtr2d/libqtr2d/libqtr2d.pro)
}

with_builtin_libqtr2d {
    QTR2dPATH = ../libqtr2d
    include(../libqtr2d/libqtr2d.pro)
}

