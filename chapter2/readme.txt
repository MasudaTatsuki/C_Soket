1. serverディレクトリ直下で以下コマンドを実行
　　　　　　　　docker-compose up 
2. コンテナ内で以下コマンドを実行してエコーサーバーを起動
　　　　　　　　chmod +X endpoint.sh
    ./endpoint.sh
※できればDockerを起動時にエコーサーバーを起動できるようにDockeFileを修正したい

3. 以下コマンドでコンテナのIPアドレスを取得する
    docker ps
    docker inspect -f '{{range .NetworkSettings.Networks}}{{.IPAddress}}{{end}}' コンテナ名またはID

4. クライアントからメッセージを送信する
　　　　　　　　./TCPEchoClient コンテナのIPアドレス "送信メッセージ"


