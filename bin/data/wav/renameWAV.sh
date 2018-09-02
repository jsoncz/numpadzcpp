for f in *.WAV; do 
    mv -- "$f" "${f%.WAV}.wav"
done
