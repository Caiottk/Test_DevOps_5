pipeline {
    agent none 

    stages {
        stage('Checkout & Info') {
            agent { label 'cpp' }
            steps {
                script {
                    echo "--- Repositório Detectado ---"
                    sh 'ls -la' 
                }
            }
        }

        stage('Build System Generation') {
            agent { label 'cpp' }
            steps {
                script {
                    echo "--- Limpando builds antigos ---"
                    sh 'rm -rf build'
                    sh 'mkdir build'
                    
                    dir('build') {
                        echo "--- Gerando Makefiles (CMake) ---"
                        sh 'cmake ..' 
                    }
                }
            }
        }

        stage('Compilation') {
            agent { label 'cpp' }
            steps {
                dir('build') {
                    echo "--- Compilando Projeto e Testes ---"
                    sh 'cmake --build .'
                }
            }
        }

        stage('Unit Tests') {
            agent { label 'cpp' }
            steps {
                dir('build') {
                    echo "--- Executando Quality Gate ---"
                    sh './run_tests'
                    
                }
            }
        }
    }

    post {
        success {
            echo '>>> SUCESSO: Pipeline Executado!'
            archiveArtifacts artifacts: 'build/calculator', fingerprint: true
        }
        failure {
            echo '>>> ERRO: Verifique o Console Output.'
        }
    }
}