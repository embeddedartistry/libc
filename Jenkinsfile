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
    stage('Report') {
      steps {
        slackSend(message: 'Build status?', channel: '#sw-notify', botUser: true)
      }
    }
  }
}