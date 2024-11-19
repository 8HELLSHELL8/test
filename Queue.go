package main

import "fmt"

type Node struct {
    content string
    next    *Node
}

type Queue struct {
    head *Node
    tail *Node
    size int // Поле для хранения размера очереди
}

func newQueue() *Queue {
    return &Queue{}
}

func (q *Queue) push(value string) {
    newNode := &Node{content: value}
    if q.tail != nil {
        q.tail.next = newNode
    }
    q.tail = newNode
    if q.isEmpty() {
        q.head = newNode
    }
    q.size++ // Увеличиваем поле размера
}

func (q *Queue) getSize() int { // Переименован метод
    return q.size
}

func (q *Queue) isEmpty() bool {
    return q.head == nil
}

func (q *Queue) printAll() {
    currentNode := q.head
    for currentNode != nil {
        fmt.Printf("%s ", currentNode.content)
        currentNode = currentNode.next
    }
    fmt.Println()
}

func (q *Queue) front() string {
    if !q.isEmpty() {
        return q.head.content
    } else {
        fmt.Println("Queue is empty!")
        return ""
    }
}

func main() {
    fmt.Println("Hello, World!")
    queue := newQueue()
    queue.push("10")
    queue.push("100")
    queue.push("1000")
    queue.printAll()             
    fmt.Println(queue.getSize()) 
}
