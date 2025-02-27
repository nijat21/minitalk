for i in {1..100}; do
  ./client 45399 "Test message $i"
  sleep 0.0
done
