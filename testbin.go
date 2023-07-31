package main

import "log"
import "os"
import "bytes"
import "encoding/binary"

type config struct {
	cpx float32
	cpy float32
	cpz float32
	crx float32
	cry float32
	crz float32
	vc int32
	nc int32
	fc int32
	mc int32
}

func main() {
	file,err := os.Create("prism.bin")
	defer file.Close()
	if err!=nil {log.Fatal(err)}
	c := &config{17,0,0,0,0,0,98234,0,0,0}
	var buf bytes.Buffer
	binary.Write(&buf,binary.LittleEndian,c)
	_,err = file.Write(buf.Bytes())
	if err!=nil {log.Fatal(err)}
}