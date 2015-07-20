module.exports = function(grunt) {
  grunt.initConfig({
    pkg: grunt.file.readJSON('package.json'),
    browserify: {
      dist: {
        files: {
          'build/app.js': ['src/app.coffee']
        },
        options: {
          transform: ['coffeeify']
        }
      }
    },
    watch: {
      files: [ "src/*.coffee"],
      tasks: [ 'browserify' ]
    }
  })
  grunt.loadNpmTasks('grunt-browserify')
  grunt.loadNpmTasks('grunt-contrib-watch')
}