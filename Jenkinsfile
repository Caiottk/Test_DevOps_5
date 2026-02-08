pipeline {
    agent none 
    
    triggers {
    
        cron('H H * * *')
    }

    options {
        timestamps()
        timeout(time: 1, unit: 'HOURS')
    }

    stages {
        stage('Checkout') {
            agent { label 'cpp' }
            steps {
                script {
                    checkout scm

                    def versionFromFile = readFile('VERSION').trim()

                    env.APP_VERSION = versionFromFile

                    echo "============================================="
                    echo "VERSÃO DEFINIDA: ${env.APP_VERSION}"
                    echo "COMMIT HASH: ${env.GIT_COMMIT}"
                    echo "============================================="
                }
            }
        }

        stage('Build (Compile)') {
            agent { label 'cpp' }
            steps {
                script {
                    sh 'rm -rf build && mkdir build'
                    
                    dir('build') {
                        sh 'cmake ..'
                        sh 'make'
                    }
                    
                    stash name: 'binario-raw', includes: 'build/calculator, build/run_tests'                
                }
            }
        }

        stage('Quality Gate (Unit Tests)') {
            agent { label 'cpp' }
            steps {
                script {
                    sh 'rm -rf build && mkdir build'
                    
                    unstash 'binario-raw'
                    
                    dir('build') {
                        sh 'chmod +x run_tests'
                        
                        sh './run_tests'
                    }
                }
            }
        }

        stage('Release & Versioning') {
            agent { label 'cpp' }
            steps {
                script {

                    unstash 'binario-raw'
                    
                    dir('build') {
                        def shortCommit = env.GIT_COMMIT.take(7)
                        def buildNum = env.BUILD_NUMBER
                        def finalName = "calculator-v${env.APP_VERSION}-b${buildNum}-${shortCommit}"

                        sh "mv calculator ${finalName}"

                        archiveArtifacts artifacts: finalName, fingerprint: true
                    }
                }
            }
        }
    }

    post {
        always {
            echo '--- Limpando Workspace para economizar disco ---'
            cleanWs() 
        }

        failure {
            echo '>>> CRÍTICO: O Pipeline falhou. Verifique os logs.'
        }

        success {
            echo ">>> SUCESSO: Pipeline da Versão ${env.APP_VERSION} finalizado."
            echo ">>> Artefato disponível para download na interface."
        }
    }
}