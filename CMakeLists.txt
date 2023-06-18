cmake_minimum_required(VERSION 3.5)
project(DITime VERSION 0.1 DESCRIPTION "Moduler for loading modules for DI engine" LANGUAGES CXX)


file( GLOB SOURCES **.cpp )

SetFlags()
SetLibraries( DIDebuger )
CreateLibrary( ${PROJECT_NAME} )