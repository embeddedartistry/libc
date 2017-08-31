pipeline {
  agent any
  stages {
    stage('Submodule Update') {
      steps {
        sh 'git submodule update'
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