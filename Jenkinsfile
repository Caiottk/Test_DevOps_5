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
                checkout scm
                echo "--- Código obtido no nó: ${env.NODE_NAME} ---"
            }
        }

        stage('Build (Compile)') {
            agent { label 'cpp' }
            steps {
                script {
                    sh 'rm -rf build && mkdir build'
                    
                    dir('build') {
                        echo "--- Configurando CMake ---"
                        sh 'cmake ..'
                        
                        echo "--- Compilando C++17 ---"
                        sh 'make'
                    }
                    
                    stash name: 'binarios-compilados', includes: 'build/calculator, build/run_tests'
                }
            }
        }

        stage('Quality Gate (Unit Tests)') {
            agent { label 'cpp' }
            steps {
                script {
                    echo "--- Preparando Ambiente de Teste ---"
                    sh 'rm -rf build && mkdir build'
                    
                    unstash 'binarios-compilados'
                    
                    dir('build') {
                        echo "--- Executando Testes Unitários ---"

                        sh 'chmod +x run_tests'
                        
                        sh './run_tests'
                    }
                }
            }
        }

        stage('Release (Archive Artifacts)') {
            agent { label 'cpp' }
            steps {
                script {

                    unstash 'binarios-compilados'
                    
                    dir('build') {
                        echo "--- Arquivando Binário Final ---"

                        archiveArtifacts artifacts: 'calculator', fingerprint: true
                    }
                }
            }
        }
    }

    post {
        failure {
            echo '>>> CRÍTICO: O Pipeline falhou. Verifique os logs.'
        }
        success {
            echo '>>> SUCESSO: Build Diário Concluído.'
        }
    }
}