pipeline {
    agent none 

    stages {
        stage('Build & Test') {
            agent { label 'cpp' }
            
            steps {
                script {
                    echo "--- Iniciando Pipeline C++17 no Agente: ${env.NODE_NAME} ---"
                    
                    sh 'rm -rf build && mkdir build'
                    
                    dir('build') {
                        sh 'cmake ..'
                        
                        echo "--- Compilando Binários ---"
                        sh 'make'
                    }
                }
            }
        }

        stage('Quality Gate: Unit Tests') {
            agent { label 'cpp' }
            steps {
                dir('build') {
                    echo "--- Executando Testes Unitários ---"
                    sh './run_tests'
                }
            }
        }
    }

    post {
        success {
            echo '>>> SUCESSO: O código C++17 compilou e passou nos testes!'

            node('cpp') {
                dir('build') {
                    archiveArtifacts artifacts: 'calculator', fingerprint: true
                }
            }
        }
        failure {
            echo '>>> FALHA: Verifique os logs de compilação ou teste.'
        }
    }
}
