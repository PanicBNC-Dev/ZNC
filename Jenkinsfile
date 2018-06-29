pipeline {
  agent any

  stages {
    stage('Pre-build') {
      steps {
        sh 'git submodule update --init --recursive'
        sh './configure.sh --prefix=$HOME/panicbnc'
      }
    }
    stage('Build') {
      steps {
        sh 'make'
        sh 'make install'
      }
    }
    stage('Integration Test') {
      steps {
        withEnv(['GTEST_OUTPUT=xml:integration-test.xml']) {            
          sh 'make VERBOSE=1 inttest'
        }
      }
    }
    stage('Tarball') {
      steps {
        sh './make-tarball.sh $BUILD_ID'
      }
    }
  }
  post {
    always {
      archiveArtifacts artifacts: 'panicbnc-*.tar.gz', onlyIfSuccessful: true
      junit '**test/*test.xml'
    }
  }
}
