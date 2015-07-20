
enum Action {
	Update,
	Remove,
}

struct Record {
    action: Action,
    domain: String,
    Username: String,
    Password: &[u8],
}

