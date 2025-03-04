for i in {1..100}; do
  ./client 46545 "Test message $i"
  sleep 0.0
done
