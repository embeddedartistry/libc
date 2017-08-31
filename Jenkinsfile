pipeline {
  agent any
  stages {
    stage('Check Downstream') {
      steps {
        sh '''git submodule init
git submodule update
git lfs pull'''
      }
    }
    stage('Build') {
      steps {
        sh 'make'
      }
    }
    stage('Check Status') {
      steps {
        catchError() {
          slackSend(message: 'Build Failed!', color: 'Red', channel: '#sw-notify', botUser: true)
        }
        
      }
    }
    stage('Report success') {
      steps {
        slackSend(message: 'Build success', channel: '#sw-notify', botUser: true, color: 'Green')
      }
    }
  }
}